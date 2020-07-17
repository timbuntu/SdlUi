#include "testing.h"

using namespace SdlUi;

int main(int argc, const char** argv) {

    TEST_ADD("Constructor", [](void) {
        assert(Vector(0,0).x == 0);
        assert(Vector(0,0).y == 0);
        assert(Vector(1,0).x == 1);
        assert(Vector(1,0).y == 0);
        assert(Vector(0,2).x == 0);
        assert(Vector(0,2).y == 2);
        assert(Vector(2,2).x == 2);
        assert(Vector(2,2).y == 2);
    });

    TEST_ADD("Comparison", [](void) {
        assert(Vector(1,3) == Vector(1,3));
        assert(Vector(1,1) <  Vector(1,3));
        assert(Vector(1,3) >  Vector(2,1));
    });

    TEST_ADD("Arithmetics", [](void) {
        Vector plusEqual(1,2);
        Vector minusEqual(3,3);

        assert(Vector(1,0) +  Vector(2,2)  == Vector(3, 2));
        assert(Vector(2,2) -  Vector(1,3)  == Vector(1,-1));
        assert((plusEqual  += Vector(1,1)) == Vector(2, 3));
        assert((minusEqual -= Vector(1,1)) == Vector(2, 2));
        assert(plusEqual                   == Vector(2, 3));
        assert(minusEqual                  == Vector(2, 2));
        assert(Vector(1,0) *  Vector(2,2)  == 2           );
        assert(Vector(0,2) *  2.5f         == Vector(0, 5));
    });
    
    TEST_ADD("Absolute", [](void) {
        assert(abs(Vector(0,0)) == 0                    );
        assert(abs(Vector(1,0)) == 1                    );
        assert(abs(Vector(0,2)) == 2                    );
        assert(abs(Vector(2,2)) == sqrt(2*2.0f + 2*2.0f));
    });
        
    runTests();
}

