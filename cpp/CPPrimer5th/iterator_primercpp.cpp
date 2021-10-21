for ( auto it = text.cbegin(); it != text.cend() && !it->empty(); ++it)
    std::cout << *it << std::end;

// in loop, don't touch vector!

// shared_ptr

shared_ptr<int> p3 = make_shared<int>(42);

// shared_ptr points to '9'*10
shared_ptr<std::string> p4 = make_shared<std::string>(10, '9');

// StrBlob - shared_ptr