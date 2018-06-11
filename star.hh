#if !defined(STAR_HH)
#define STAR_HH

#include <cmath>

#include "vec2d.hh"

class star {
public:
  // Create a new star with a given position and velocity
  star(float mass, vec2d pos, vec2d vel, rgb32 color) : 
      _mass(mass),
      _radius(pow(_mass / 3.14, 0.33) / 4),
      _pos(pos),
      _vel(vel),
      _force(0, 0),
      _color(color),
      _initialized(false) {}
  
  // Update this star's position with a given force and a change in time
  void update(float dt) {
    vec2d accel = _force / _mass;
    
    // Verlet integration
    if(!_initialized) { // First step: no previous position
      vec2d next_pos = _pos + _vel * dt + accel / 2 * dt * dt;
      _prev_pos = _pos;
      _pos = next_pos;
      _initialized = true;
    } else {  // Later steps: 
      vec2d next_pos = _pos * 2 - _prev_pos + accel * dt * dt;
      _prev_pos = _pos;
      _pos = next_pos;
    }
    
    // Track velocity, even though this isn't strictly required
    _vel += accel * dt;
    
    // Zero out the force
    _force = vec2d(0, 0);
  }
  
  // Add a force on this star
  void addForce(vec2d force) {
    _force += force;
  }
  
  // Get the position of this star
  vec2d pos() { return _pos; }
  
  // Get the velocity of this star
  vec2d vel() { return _vel; }
  
  // Get the mass of this star
  float mass() { return _mass; }
  
  // Get the radius of this star
  float radius() { return _radius; }
  
  // Get the color of this star
  rgb32 color() { return _color; }
  
  // Merge two stars
  star merge(star other) {
    float mass = _mass + other._mass;
    vec2d pos = (_pos * _mass + other._pos * other._mass) / (_mass + other._mass);
    vec2d vel = (_vel * _mass + other._vel * other._mass) / (_mass + other._mass);
    
    rgb32 color = rgb32(
      ((float)_color.red*_mass + (float)other._color.red*other._mass) / (_mass + other._mass),
      ((float)_color.green*_mass + (float)other._color.green*other._mass) / (_mass + other._mass),
      ((float)_color.blue*_mass + (float)other._color.blue*other._mass) / (_mass + other._mass));
    
    return star(mass, pos, vel, color);
  }
  
private:
  float _mass;        // The mass of this star
  float _radius;      // This star's radius (depends on mass)
  vec2d _pos;         // The position of this star
  vec2d _prev_pos;    // The previous position of this star
  vec2d _vel;         // The velocity of this star
  vec2d _force;       // The accumulated force on this star
  rgb32 _color;       // The color of this star
  bool _initialized;  // Has this particle been updated at least once?
};

#endif
