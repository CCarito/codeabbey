import math

def simulate_landing(mass_craft, mass_fuel, initial_height, descent_velocity, burn_rates):
    moon_radius = 1737100  # meters
    gravity = 1.622  # m/s^2
    exhaust_speed = 2800  # m/s
    dt = 0.1  # seconds

    height = initial_height
    velocity = descent_velocity
    fuel_consumed = 0
    index = 0

    while height > 0:
        if index < len(burn_rates):
            burn_rate = burn_rates[index]
            index += 1
        else:
            burn_rate = 0

        if mass_fuel > 0:
            fuel_consumed += burn_rate * dt
            if fuel_consumed > mass_fuel:
                fuel_consumed = mass_fuel
            mass_fuel -= fuel_consumed

            exhaust_velocity = exhaust_speed * math.log((mass_craft + mass_fuel) / mass_craft)
            thrust = burn_rate * exhaust_velocity
            mass_craft -= (burn_rate * dt)

            acceleration = gravity - (thrust / (mass_craft + mass_fuel))
        else:
            acceleration = gravity

        velocity += acceleration * dt
        height -= velocity * dt

    return abs(velocity)

# Read input data
mass_craft, mass_fuel, initial_height, descent_velocity = map(int, input().split())
burn_rates = list(map(int, input().split()))

# Simulate landing and calculate speed on reaching the Moon's surface
speed = simulate_landing(mass_craft, mass_fuel, initial_height, descent_velocity, burn_rates)
print(round(speed))
