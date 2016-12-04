#include "ConstructionWorker.h"

ConstructionWorker::ConstructionWorker()
: state(State::WORK)
, counter(0)
{}

void ConstructionWorker::go_work() {
    if (state == State::WORK) {
        return;
    }
    if (counter < MIN_REST_TIME) {
        throw std::runtime_error("Can't go work: worker not rested enough");
    }
    counter = 0;
    state = State::WORK;
}

void ConstructionWorker::go_rest() {
    if (state == State::REST) {
        return;
    }
    counter = 0;
    state = State::REST;
}

void ConstructionWorker::rest(unsigned minutes) {
    if (state != State::REST) {
        throw std::runtime_error("Can't rest: worker is at work");
    }
    counter += minutes;
}

void ConstructionWorker::lay_bricks(unsigned n_bricks) {
    if (state != State::WORK) {
        throw std::runtime_error("Can't lay bricks: worker is at rest");
    }
    if (counter + n_bricks > MAX_BRICKS_BETWEEN_REST) {
        throw std::runtime_error("Can't lay bricks: worker needs rest");
    }
    counter += n_bricks;
}

unsigned ConstructionWorker::bricks_laid() const {
    if (state != State::WORK) {
        throw std::runtime_error("Can't get number of laid bricks: worker is at rest");
    }
    return counter;
}

unsigned ConstructionWorker::minutes_rested() const {
    if (state != State::REST) {
        throw std::runtime_error("Can't get resting time: worker is at work");
    }
    return counter;
}

ConstructionWorker::State ConstructionWorker::get_state() const {
    return state;
}
