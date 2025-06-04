#moon_landing.cpp
#include <iostream>
using namespace std;

int main() {
    double height = 100.0;       // in meters
    double velocity = 0.0;       // in m/s
    double fuel = 100.0;         // in liters
    double gravity = 1.6;        // Moon gravity in m/s^2
    int time = 0;

    cout << "🚀 Moon Lander Game 🚀" << endl;
    cout << "Land safely with a speed less than 5 m/s!" << endl;

    while (height > 0) {
        cout << "\nTime: " << time << "s"
             << " | Height: " << height << "m"
             << " | Velocity: " << velocity << "m/s"
             << " | Fuel: " << fuel << "L" << endl;

        double burn;
        cout << "Enter fuel to burn (0-10): ";
        cin >> burn;

        // Sanitize input
        if (burn < 0) burn = 0;
        if (burn > 10) burn = 10;
        if (burn > fuel) burn = fuel;

        fuel -= burn;
        double accel = gravity - burn * 0.3;  // each unit of fuel gives some thrust
        velocity += accel;
        height -= velocity;
        if (height < 0) height = 0;
        time++;
    }

    cout << "\nFinal velocity: " << velocity << " m/s" << endl;
    if (velocity <= 5.0)
        cout << "🎉 You landed safely on the Moon!" << endl;
    else
        cout << "💥 Crash! You hit the Moon too hard." << endl;

    return 0;
}
