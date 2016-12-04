#include <cxxtest/TestSuite.h>
#include <memory>
#include "../src/ConstructionWorker.h"


#define ASSERT_EXPECTED_ERROR(expr, message) \
    TS_ASSERT_THROWS_EQUALS(expr, const std::runtime_error &e, e.what(), message)


class ConstructionWorkerTestsBase : public CxxTest::TestSuite {
protected:
    std::shared_ptr<ConstructionWorker> worker;

public:

    virtual void setUp() {
        worker.reset(new ConstructionWorker());
    }
};


class TestConstructionWorkerInitialState : public ConstructionWorkerTestsBase {
public:

    void test_initial_state() {
        TS_ASSERT_EQUALS(
                worker->get_state(),
                ConstructionWorker::State::WORK
        );
    }

};


class TestConstructionWorkerAtRest : public ConstructionWorkerTestsBase {
public:

    virtual void setUp() {
        ConstructionWorkerTestsBase::setUp();
        worker->go_rest();
    }

    void test_state() {
        TS_ASSERT_EQUALS(
            worker->get_state(),
            ConstructionWorker::State::REST
        );
    }

    void test_can_not_inspect_its_work() {
        ASSERT_EXPECTED_ERROR(
            worker->bricks_laid(),
            "Can't get number of laid bricks: worker is at rest"
        );
    }

    void test_can_not_lay_bricks() {
        ASSERT_EXPECTED_ERROR(
            worker->lay_bricks(1),
            "Can't lay bricks: worker is at rest"
        );
    }

    void test_go_rest_does_nothing() {
        worker->rest(100);
        worker->go_rest();
        TS_ASSERT_EQUALS(worker->get_state(), ConstructionWorker::State::REST);
        TS_ASSERT_EQUALS(worker->minutes_rested(), 100);
    }

    void test_rest_method_works() {
        TS_ASSERT_EQUALS(worker->minutes_rested(), 0);
        worker->rest(10);
        TS_ASSERT_EQUALS(worker->minutes_rested(), 10);
        worker->rest(25);
        TS_ASSERT_EQUALS(worker->minutes_rested(), 10+25);
    }

    void test_required_minimal_rest_time() {
        worker->rest(ConstructionWorker::MIN_REST_TIME-1);
        ASSERT_EXPECTED_ERROR(
            worker->go_work(),
            "Can't go work: worker not rested enough"
        );
        TS_ASSERT_EQUALS(worker->get_state(), ConstructionWorker::State::REST);
        worker->rest(1);
        TS_ASSERT_THROWS_NOTHING(worker->go_work());
        TS_ASSERT_EQUALS(worker->get_state(), ConstructionWorker::State::WORK);
    }

    void test_restarting_rest_resets_rest_time() {
        worker->rest(10);
        worker->go_work();
        worker->go_rest();
        TS_ASSERT_EQUALS(worker->minutes_rested(), 0);
    }

};


class TestConstructionWorkerAtWork : public ConstructionWorkerTestsBase {
public:

    void test_state() {
        TS_ASSERT_EQUALS(
            worker->get_state(),
            ConstructionWorker::State::WORK
        );
    }

    void test_can_not_inspect_its_rest() {
        ASSERT_EXPECTED_ERROR(
            worker->minutes_rested(),
            "Can't get resting time: worker is at work"
        );
    }

    void test_can_not_rest() {
        ASSERT_EXPECTED_ERROR(
            worker->rest(1),
            "Can't rest: worker is at work"
        );
    }

    void test_go_work_does_nothing() {
        worker->lay_bricks(10);
        worker->go_work();
        TS_ASSERT_EQUALS(worker->get_state(), ConstructionWorker::State::WORK);
        TS_ASSERT_EQUALS(worker->bricks_laid(), 10);
    }

    void test_lay_bricks_works() {
        TS_ASSERT_EQUALS(worker->bricks_laid(), 0);

        worker->lay_bricks(5);
        TS_ASSERT_EQUALS(worker->bricks_laid(), 5);

        worker->lay_bricks(7);
        TS_ASSERT_EQUALS(worker->bricks_laid(), 5+7);

        const unsigned up_to_max = ConstructionWorker::MAX_BRICKS_BETWEEN_REST - (5+7);
        worker->lay_bricks(up_to_max);
        TS_ASSERT_EQUALS(worker->bricks_laid(), ConstructionWorker::MAX_BRICKS_BETWEEN_REST);
    }

    void test_can_not_lay_too_many_bricks() {
        worker->lay_bricks(ConstructionWorker::MAX_BRICKS_BETWEEN_REST);
        ASSERT_EXPECTED_ERROR(
            worker->lay_bricks(1),
            "Can't lay bricks: worker needs rest"
        );
        TS_ASSERT_EQUALS(worker->bricks_laid(), ConstructionWorker::MAX_BRICKS_BETWEEN_REST);
    }

    void test_lay_bricks_can_not_be_partial() {
        worker->lay_bricks(5);
        ASSERT_EXPECTED_ERROR(
            worker->lay_bricks(ConstructionWorker::MAX_BRICKS_BETWEEN_REST),
            "Can't lay bricks: worker needs rest"
        );
        TS_ASSERT_EQUALS(worker->bricks_laid(), 5);
    }

    void test_restarting_work_resets_bricks_counter() {
        worker->lay_bricks(5);

        worker->go_rest();
        worker->rest(ConstructionWorker::MIN_REST_TIME);
        worker->go_work();

        TS_ASSERT_EQUALS(worker->bricks_laid(), 0);
    }
};

