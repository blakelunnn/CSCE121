#include <iostream>
#include <cmath>
#include "./nth_root.h"

int main() {
    {   // MINIMUM REQUIREMENT (for this lab)
        // just call the function with various values of n and x
        
		try { 
            nth_root(0,5);
			nth_root(-100, 0);
			nth_root(4,-2);
			
            std::cout << "[FAIL] expected on exception, none thrown." << std::endl;
        } 
        catch (std::domain_error) {
            std::cout << "[PASS] caught an exception." << std::endl;
        } 
		
		nth_root(3, -2);
		nth_root(2, 1);
		nth_root(1, 5);
		nth_root(6, 2);
		nth_root(-1,6);
		nth_root(-6, 2);
		nth_root(-5, 3);
		nth_root(12, 0);
		nth_root(10, 3.5);
		

    }

    {   // TRY HARD
        // report the value
        double actual = nth_root(2, 1);
        std::cout << "nth_root(2, 1) = " << actual << std::endl;
		actual = nth_root(3, -2);
		std::cout << "nth_root(3, -2) = " << actual << std::endl;
		actual = nth_root(12, 0);
		std::cout << "nth_root(12, 0) = " << actual << std::endl;
    }

    {   // TRY HARDER
        // compare the actual value to the expected value
        double actual = nth_root(2, 1);
        double expected = 1;
        if (std::fabs(actual - expected) > 0.00005) {
            std::cout << "[FAIL] (n=2, x=1)" << std::endl;
            std::cout << "  expected nth_root(2, 1) to be " << expected << std::endl;
            std::cout << "  got " << actual << std::endl;
        } else {
            std::cout << "[PASS] (n=2, x=1)" << std::endl;
        }
    }
}
