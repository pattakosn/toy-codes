class nsp_time {
  void start() { now(start); };
  void end() {
    now(end);
    auto diff = end - start;
    auto t1 = std::chrono::duration_cast<std::chrono::nanoseconds>(diff);
    std::cout << "\t+++++NIKOS+++++\t Convolve2d time: " << t1.count() << std::endl;
  };

  private:
  time_point<steady_clock> start;
  time_point<steady_clock> end;
  void now(time_point<steady_clock>& when) { when = std::chrono::high_resolution_clock::now(); };
};
