#include "ConstructionWorker.h"

ConstructionWorker::ConstructionWorker() {

}

void ConstructionWorker::go_work() {

}

void ConstructionWorker::go_rest() {

}

void ConstructionWorker::rest(unsigned minutes) {

}

void ConstructionWorker::lay_bricks(unsigned n_bricks) {

}

unsigned ConstructionWorker::bricks_laid() const {
    return 0;
}

unsigned ConstructionWorker::minutes_rested() const {
    return 0;
}

ConstructionWorker::State ConstructionWorker::get_state() const {
    return State::WORK;
}
