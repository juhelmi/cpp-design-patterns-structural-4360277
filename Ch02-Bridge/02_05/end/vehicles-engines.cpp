#include <iostream>
#include <memory>
#include <format>

using namespace std;

class IEngine
{
public:
    virtual void start() const = 0;
    virtual string getSound() const = 0;
    virtual ~IEngine() = default;
};

class IVehicle
{
public:
    explicit IVehicle(const IEngine &engine) : m_engine(engine) {}

    void drive() 
    {
        m_engine.start();
        driveVehicle();
    }

    virtual ~IVehicle() = default;

protected:
    virtual void driveVehicle() /*const = 0*/{};

public:
    string getNoise()
    {
        return m_engine.getSound();
    }

private:
    const IEngine &m_engine;
};

// Concrete implementation of Gas engine
class GasEngine : public IEngine
{
public:
    void start() const override
    {
        cout << "Starting gas engine." << endl;
    }
    string getSound() const override
    {
        return "Burrr";
    }
};

// Concrete implementation of Electric engine
class ElectricEngine : public IEngine
{
public:
    void start() const override
    {
        cout << "Starting electric engine." << endl;
    }
    string getSound() const override
    {
        return "Zzrr";
    }
};

// Concrete implementation of Hybrid engine
class HybridEngine : public IEngine
{
public:
    void start() const override
    {
        cout << "Starting hybrid engine." << endl;
    }
    string getSound() const override
    {
        return "..burr..";
    }
};

class SteamEngine : public IEngine
{
public:
    void start() const override
    {
        cout << "Warming steam engine." << endl;
    }
    string getSound() const override
    {
        return "Fiii";
    }
};

// Concrete implementation of Car
class Car : public IVehicle
{
public:
    Car(const IEngine &engine) : IVehicle(engine) {}

    void driveVehicle() override
    {
        cout << "Driving a car. " << getNoise() << endl;
    }
};

// Concrete implementation of Truck
class Truck : public IVehicle
{
public:
    Truck(const IEngine &engine) : IVehicle(engine) {}

    void driveVehicle()  override
    {
        cout << format("Driving a truck. {}", getNoise()) << endl;
    }
};

// Concrete implementation of Bike
class Bike : public IVehicle
{
public:
    Bike(const IEngine &engine) : IVehicle(engine) {}

    void driveVehicle()  override
    {
        // cout << format("Riding a bike. Sound {}", getNoise()) << endl;
        cout << "Riding a bike. Sound " << getNoise() << endl;
    }
};

int main()
{
    auto gasEngine = GasEngine();
    auto electricEngine = ElectricEngine();
    auto hybridEngine = HybridEngine();
    auto steamEngine = SteamEngine();

    // Create an array of pointers to Vehicle objects.
    const std::unique_ptr<IVehicle> vehicles[]{
        make_unique<Car>(gasEngine),
        make_unique<Truck>(electricEngine),
        make_unique<Bike>(hybridEngine),
        make_unique<Bike>(electricEngine),
        make_unique<Bike>(steamEngine)};

    for (const auto &vehicle : vehicles)
    {
        vehicle->drive();
        cout << endl;
    }

    return 0;
}
