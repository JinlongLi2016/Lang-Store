// PopOnEmpty & PushOnFull

class StackException: public logic_error{
    StackException(const char *what): _what(what){}
    const char * what() const { return _what};
}

class PopOnEmpty: public StackException {
    PopOnEmpty(): StackException("Pop On Empty Stack."){}
}

class PushOnFull: public StackException {
    PushOnFull(): StackException("Push On Full"){};
}