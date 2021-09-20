#include <iostream>
#include <sstream>
#include <vector>
#include <memory>

struct TestCase { std::string name{}; std::ostringstream failures{}; };
template <typename T> void operator | (TestCase& testCase, T&& testBody) {
    testBody(); auto failures = testCase.failures.str();
    if (failures.empty()) std::cout << testCase.name << ": SUCCESS\n";
    else std::cerr << testCase.name << ": FAILURE\n" << failures;
}
void addFailure(std::ostream& os, const char* file, unsigned line, const char* condition) {
    os << file << ":" << line << ": Failed: " << condition << "\n";
}
#define TEST(name) TestCase name{#name}; name | [&, &failures = name.failures]
#define EXPECT(cond) if (cond) {} else addFailure(failures, __FILE__, __LINE__, #cond)
#define ASSERT(cond) if (cond) {} else return addFailure(failures, __FILE__, __LINE__, #cond)

struct Temperature{
    private:
        int temperatureCelsius = 21;
        int temperatureKelvin = temperatureCelsius + 273;
        const int conversionNumber = 273;
    public:
    int getCel() {
        return temperatureCelsius;
    }
    int getKelvin() {
        return temperatureCelsius+273;
    }
    void setCel(int temp_) {
        temperatureCelsius = temp_;
        temperatureKelvin = temp_ + conversionNumber;
    }
    void setKelvin(int temp_){
        temperatureKelvin = temp_;
        temperatureCelsius = temp_ - conversionNumber;
    }
};

class Device{};

class Station{
    Temperature termometer;
    int old_temp = 0;
    std::vector<Device> listOfDevices{};
    public:
    Station(const Temperature& termometer):termometer(termometer){};
    int getTemperature(){
        int actual_temp = termometer.getCel();
        if(actual_temp!=old_temp){
            old_temp = actual_temp;
            return actual_temp;
        }
        return old_temp;
    }

    void attach(Device device){
        listOfDevices.push_back(device);
    }
    
    std::size_t numberOfDevices(){
        return listOfDevices.size();
    }

};

int main() 
{
    TEST(GivenTemperatureForUserObjectAndExpectTemperature)
    {
        Temperature temp;
        temp.setCel(10);

        Device device;
        Station station(temp);
        station.attach(device);
        EXPECT(station.numberOfDevices() == 1);
    };
TEST(GivenTemperatureForUserObjectAndExpectTemperature)
    {
        Temperature temp;
        temp.setCel(10);

        Device device;
        Station station(temp);
        station.attach(device);
        EXPECT(station.numberOfDevices() == 1);
    };

    TEST(GivenTemperatureObjectAndExpectTemperature)
    {
        Temperature temp;
        temp.setCel(-1);
        Station station(temp);
        EXPECT(station.getTemperature() == temp.getCel());
    };

    TEST(TemperatureSensorShouldReturnTemperatureinKelvinAfterSet295)
    {
        Temperature temp;
        temp.setKelvin(295);
        EXPECT(temp.getKelvin() == 295);
    };
    TEST(TemperatureSensorShouldReturnTemperatureinCelsAfterSet22)
    {
        Temperature temp;
        temp.setCel(22);
        EXPECT(temp.getCel() == 22);
    };

    TEST(TemperatureSensorShouldReturnTemperature)
    {
        
        EXPECT(Temperature().getCel() == 21);
    };

        TEST(TemperatureSensorShouldReturnTemperatureinKelvin)
    {
        
        EXPECT(Temperature().getKelvin() == 294);
    };
}