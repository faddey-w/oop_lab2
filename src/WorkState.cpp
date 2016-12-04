#include "WorkState.h"
#include "RestState.h"

IWorkerState* WorkState::go_work() {
    return this;
};
IWorkerState* WorkState::go_rest() {
    return new RestState;
};

void WorkState::rest(unsigned minutes) {
    throw std::runtime_error("Can't rest: worker is at work");
};
void WorkState::lay_bricks(unsigned n_bricks) {
    if (n_bricks_laid + n_bricks > ConstructionWorker::MAX_BRICKS_BETWEEN_REST) {
        throw std::runtime_error("Can't lay bricks: worker needs rest");
    }
    n_bricks_laid += n_bricks;
};

unsigned WorkState::bricks_laid() const {
    return n_bricks_laid;
};
unsigned WorkState::minutes_rested() const {
    throw std::runtime_error("Can't get resting time: worker is at work");
};
ConstructionWorker::State WorkState::get_state_id() const {
    return WorkerStateId ::WORK;
};
