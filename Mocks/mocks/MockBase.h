class MockBase : public Base {
 public:
  MOCK_CONST_METHOD0(getName,
      std::string());
  MOCK_CONST_METHOD0(getId,
      unsigned int());
};
