#include <vector>
#include <cstddef>
#include <functional>
#include <future>
#include <queue>
#include <thread>

class Threads {
public:
Threads(size_t Size) : in_progress(true) {
    for (size_t i = 0; i < Size; ++i) {
        threads.emplace_back(
                [this]() {
                    while (in_progress) {
                        std::unique_lock<std::mutex> lock(mutex_);
                        if (!Queue.empty()) {
                            auto task = Queue.front();
                            Queue.pop();
                            lock.unlock();
                            task();
                        } else {
                            cond_var.wait(lock);
                        }
                    }
                });
    }
}

~Threads() {
    in_progress = false;
    cond_var.notify_all();
    for (auto& thread : threads) {
        thread.join();
    }
}
    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))> {
        using typeReturn = decltype(func(args...));
        using typeP = std::packaged_task<typeReturn ()>;
        auto task = std::make_shared<typeP>([func, args...]() {
            return func(args...);
        });
        {
            std::lock_guard<std::mutex> lock(mutex_);
            Queue.emplace(
                    [task]() {
                        (*task)();
                    });
        }
        cond_var.notify_one();
        return task->get_future();
    }
private:
    using Task = std::function<void ()>;
    std::atomic<bool> in_progress;
    std::vector<std::thread> threads;
    std::queue<Task> Queue;
    std::mutex mutex_;
    std::condition_variable cond_var;
};