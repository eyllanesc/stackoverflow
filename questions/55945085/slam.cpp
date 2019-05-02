#include <iostream>
#include <thread>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

class Slam{
public:
    Slam(): m_value(0){}
    void setParams(int value){
        m_value = value;
    }
    int start(){
        // pybind11::gil_scoped_release release;
        using namespace std::chrono_literals;
        for (int i{0}; i< m_value; ++i) {
        	std::cout << i << std::endl;
            std::this_thread::sleep_for(1s);
        }
        //pybind11::gil_scoped_acquire acquire;
        return 0;
    }
private:
    int m_value;
};

PYBIND11_MODULE(pyslam, mymodule) {
    using namespace pybind11::literals; // for _a literal to define arguments
    mymodule.doc() = "slam module";
    pybind11::class_<Slam>(mymodule, "Slam")
          .def(pybind11::init<>())
          .def("setParams", &Slam::setParams)
          .def("start", &Slam::start, pybind11::call_guard<pybind11::gil_scoped_release>());
#ifdef VERSION_INFO
    mymodule.attr("__version__") = VERSION_INFO;
#else
    mymodule.attr("__version__") = "dev";
#endif
}
