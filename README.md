IdOp
====

## C++ Custom Operator Library

IdOp allows you to build custom pseudo-operators using a few simple macros. The macros generate several templates which can be entirely statically evaluated. Here is a short example:

    template<typename T> class AssertOp {
    public:
        void operator()(const T& left, const T& right) const
        { assert(left != right); }
    };
    IDOP_CREATE_LEFT_HANDED_RET(^, _, ^, AssertOp, void)

This defines a pseudo-operator, ^_^, which can be used like the following:

    int foo(int* bar)
    {
        bar ^_^ NULL;
        // ...
    }
    
You can also construct more sober operators like:

    if ("Hello, world!" contains "Hello") // ...  

See IdOpExamples.cpp or the [IdOp Reference](http://cogwheel.info/idop/reference.html) for more information.

Requires Boost.Preprocessor

## History

2009-10-05 20:33 - v1.0.1
Fixed compilation on gcc.

2009-10-05 15:14 - v1.0
Operations can modify either operand.

2009-10-03 16:57 - v0.9
Initial release.

Bugs or Comments?

E-mail me at cogwheel@cogwheel.info
