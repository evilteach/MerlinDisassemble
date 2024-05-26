#include "MiniCppUnit.hxx"

class MyTestsExample : public TestFixture<MyTestsExample>
{
    public:

        TEST_FIXTURE( MyTestsExample )
        {
            TEST_CASE( testAddition );
            TEST_CASE( testSubstraction );
            TEST_CASE( testException );
            TEST_CASE( testStringAddition );
        }

        void testAddition()
        {
            ASSERT_EQUALS( 2, 1+1 );
        }

        void testSubstraction()
        {
            double result = 10.0 - 9.9999;
            ASSERT_MESSAGE( result <= 0.0001, "10 - 9.9999 should give something <= 0.0001");
        }

        void testException()
        {
            try
            {
                someCodeThatShouldThrowException();
                FAIL( "Should have raised an exception" );
            }
            catch (std::exception &e)
            {
                (void) e;
                // maybe assert for string in e.what()
            }
        
        }

        void testStringAddition()
        {
            std::string result("Hello");
            result += " World";
            ASSERT_EQUALS("Hello World", result);
        }
    
    private:
        void someCodeThatShouldThrowException()
        {
            throw std::exception();
        }
};

REGISTER_FIXTURE( MyTestsExample );
