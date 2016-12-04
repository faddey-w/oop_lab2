#include "RestState.h"
#include "WorkState.h"

IWorkerState* RestState::go_work() {
    if (n_minutes_rested < ConstructionWorker::MIN_REST_TIME) {
        throw std::runtime_error("Can't go work: worker not rested enough");
    }
    return new WorkState;
};
IWorkerState* RestState::go_rest() {
    return this;
};

void RestState::rest(unsigned minutes) {
    n_minutes_rested += minutes;
};
void RestState::lay_bricks(unsigned n_bricks) {
    throw std::runtime_error("Can't lay bricks: worker is at rest");
};

unsigned RestState::bricks_laid() const {
    throw std::runtime_error("Can't get number of laid bricks: worker is at rest");
};
unsigned RestState::minutes_rested() const {
    return n_minutes_rested;
};
ConstructionWorker::State RestState::get_state_id() const {
    return WorkerStateId::REST;
};
