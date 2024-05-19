#include "AnimationModule.h"
#include "InputModule.h"
#include "RenderModule.h"
#include "../utils/ResourceManager.h"

// Constructor
AM::AnimationModule(flecs::world& world) {
    // Import required modules
    world.import<InputModule>();
    world.import<TransformModule>();

    // Create an observer for the "OnSet:AnimationState" event
    world.observer<RM::Type, Animation::State>("OnSet:AnimationState")
        .event(flecs::OnSet)
        .each([](flecs::entity entity, RM::Type& type, Animation::State& state) {
            // Get sprite data for the given animation type
            auto data = RSC::getSpriteData(type.type);

            // Get the Frame and Animation components for the entity
            auto animation = entity.get_mut<Frame, Animation>();

            // Grab the new set of frames and reset the current frame
            animation->frames = data.animations[state.state];
            animation->currentFrame = 0;
        });

    // Create a system for updating frame-based animations
    world.system<Frame>("UpdateFrameAnimation")
        .term_at(1).second<Animation>()
        .kind(flecs::PreStore)
        .each(updateFrame);

    // Create a system for updating linear animations
    world.system<Linear, TM::Position>("UpdateLinearAnimation")
        .term_at(1).second<Animation>()
        .kind(flecs::PreStore)
        .each(updateLinear);

    // Create a system for updating interactivity based on mouse input
    world.system<IM::Mouse>("UpdateInteractivity")
        .each(updateInteractivity);
}

// Function for updating frame-based animations
void AM::updateFrame(Frame& frame) {
    frame.frameTime += GetFrameTime();

    // Advance to the next frame when the time is right
    const int ANIMATION_FRAME_RATE = 12;

    if (frame.frameTime >= 1.0 / ANIMATION_FRAME_RATE) {
        frame.currentFrame++;
        frame.frameTime = 0;
    }

    // Reset to the first frame if the end of the animation is reached
    if (frame.currentFrame >= frame.frames.size()) {
        frame.currentFrame = 0;
    }
}

// Function for updating linear animations
void AM::updateLinear(Linear& linear, TM::Position& position) {
    // Calculate the total distance to travel
    float totalDistance = sqrt(pow(linear.end.x - linear.start.x, 2) + pow(linear.end.y - linear.start.y, 2));

    // Calculate the speed needed to travel the total distance in the desired duration
    float speed = totalDistance / linear.duration;

    // Calculate the normalized direction vector
    Vector2 direction = {
        (linear.end.x - linear.start.x) / totalDistance,
        (linear.end.y - linear.start.y) / totalDistance
    };

    // Update the position based on the speed and direction
    position.x += speed * direction.x * GetFrameTime();
    position.y += speed * direction.y * GetFrameTime();

    // Check if the current position has reached the end position
    bool hasReachedEnd = position.x >= linear.end.x && position.y >= linear.end.y;

    // If the end is reached, reset the position to the start
    if (hasReachedEnd) {
        position.x = linear.start.x;
        position.y = linear.start.y;
    }
}

// Function for updating interactivity based on mouse input
void AM::updateInteractivity(flecs::entity entity, const IM::Mouse mouse) {
    ANIMATIONS state = ANIMATIONS::IDLE;

    // Determine the animation state based on mouse input
    if (mouse.isLeftPressed) {
        state = ANIMATIONS::PRESS;
    }
    if (mouse.isRightPressed) {
        state = ANIMATIONS::PRESS;
    }

    // Set the Animation::State component for the entity
    entity.set<Animation::State>({state});
}
