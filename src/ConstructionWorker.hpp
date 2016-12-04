#ifndef CONSTRUCTIONWORKER_H
#define CONSTRUCTIONWORKER_H

#include <map>
#include <memory>
#include <exception>


enum WorkerStateId {WORK, REST};


class IWorkerState {
public:

    typedef std::shared_ptr<IWorkerState> Ptr;

    virtual IWorkerState* go_work() = 0;
    virtual IWorkerState* go_rest() = 0;

    virtual void rest(unsigned minutes) = 0;
    virtual void lay_bricks(unsigned n_bricks) = 0;

    virtual unsigned bricks_laid() const = 0;
    virtual unsigned minutes_rested() const = 0;
    virtual WorkerStateId get_state_id() const = 0;

};

class ConstructionWorker {
public:

    using State = WorkerStateId;
    static const unsigned MIN_REST_TIME = 15;
    static const unsigned MAX_BRICKS_BETWEEN_REST = 20;

    ConstructionWorker(IWorkerState::Ptr &initial_state)
        : state(initial_state) {}

    void go_work() {
        IWorkerState* new_state = state->go_work();
        if (new_state != state.get()) {
            state.reset(new_state);
        }
    };
    void go_rest() {
        IWorkerState* new_state = state->go_rest();
        if (new_state != state.get()) {
            state.reset(new_state);
        }
    };
    void rest(unsigned minutes) {
        state->rest(minutes);
    };
    void lay_bricks(unsigned n_bricks) {
        state->lay_bricks(n_bricks);
    };

    unsigned bricks_laid() const {
        return state->bricks_laid();
    };
    unsigned minutes_rested() const {
        return state->minutes_rested();
    };
    State get_state() const {
        return state->get_state_id();
    };

private:

    IWorkerState::Ptr state;
};


#endif // CONSTRUCTIONWORKER_H
