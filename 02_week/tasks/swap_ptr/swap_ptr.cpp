void SwapPtr(auto& a, auto& b) {
    auto tmp = a;

    a = b;
    b = tmp;
}