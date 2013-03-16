//
//  Sprite.cpp
//  GLSFMLEngine
//
//  Created by Evan Chapman on 3/10/13.
//  Copyright (c) 2013 Evan Chapman. All rights reserved.
//

#include "Sprite.h"

/*
 ===================
 Constructor
 ===================
 */
Sprite::Sprite() {
    //Just used for testing
    isLooping = true;
    isTurning = false;
    isJumping = false;
    isAnimated = true;
    isFalling = false;
    isJumping = false;
    isStopped = true;
    isStopping = false;
    animationDelay = .50f;
    SetAnimation(0);
    currentAnimation = 0;
    currentFrame = 0;
    currentFrameIndex = 0;
    
    
    acceleration.x = 0;
    acceleration.y = 0;
    friction.x  = 0.0f;
    friction.y = 0.0f ;
    maxFriction.x = 0.0f;
    maxFriction.y = 0.0f;
    
    maxVelocity.x = 0.0f;
    maxVelocity.y = 0.0f;
    
    minVelocity.x = -0.0f;
    minVelocity.y = -0.0f;
    velocity.x = 0;
    velocity.y = 0;
    
    
    R=G=B= 1.5f;
}


Sprite::~Sprite() {
    //animation.index.clear();
}


/*
 ========================
 Draw()
    Draw current frame of animation to quad area
 ========================
 */
void Sprite::Draw() {
    //Select Current Frame of animation texture
    glBindTexture( GL_TEXTURE_2D, currentFrame );
    
    //Begin drawing area
    glBegin( GL_QUADS );
    glColor3f( R, G, B );
    
    glTexCoord2f( 0, 0 );//Bottom Left
    glVertex3f( position.x, position.y, position.z );
    glTexCoord2f( 1, 0 );//Bottom Right
    glVertex3f( position.x + size.x, position.y, position.z );
    glTexCoord2f( 1, 1 );//Top Right
    glVertex3f( position.x + size.x, position.y - size.y,position.z );
    glTexCoord2f( 0, 1 );//Top left
    glVertex3f( position.x, position.y - size.y,position.z );
    glEnd();
}



//Animation
//-----------------------------------------

/*
 ====================
 AddFrame
 Add texture to new frame of animation
 ====================
 */
void Sprite::AddFrame(const std::string& filename, int animationIndex ) {
    int textureID = texture.Load(filename);
    if ( textureID == 0 ) {
        textureID = 1;
    }
    animation.index[animationIndex].push_back(textureID);
}



/*
 ===============
 AddAnimation
 Add chunk of animation frames
 ===============
 */
void Sprite::AddAnimation(vector<int> newAnimation) {
    animation.index.push_back( newAnimation );
    numberOfAnimations++;
}

/*
 Remove animation
 Remove chunk of animation frames
 */
void Sprite::RemoveAnimation(int indexToRemove) {
    animation.index.erase(animation.index.begin() + indexToRemove );
    numberOfAnimations--;
}

/*
 Set Animation
 Set animation to index
 */
void Sprite::SetAnimation( int index ) {
    if ( index <= numberOfAnimations) {
    currentAnimation = index;
    } else {
        currentAnimation =  0;
    }
}

/*
 ================
 Set animation delay
 Set the delay between frame changes
 ================
 */
void Sprite::SetAnimationDelay( float delay ) {
    animationDelay = delay;
}

/*
 ==========================
 Animate
 Advance frame, if frame is beyond boundaries
 of current animation, loop animation if animation is looped
 ==========================
 */
void Sprite::Animate(float deltaTime) {
    /*
    if ( deltaTime >= 10.0f ) {
        deltaTime = 10.0f;
    }
    
    if ( deltaTime < 0 ) {
        deltaTime = 0;
    }
    */
    animationDelayTotal += deltaTime;
    
    if ( animationDelayTotal >= animationDelay && isAnimated ) {
        animationDelayTotal = 0;
        currentFrameIndex++;
    }
    
    unsigned long lastFrame = animation.index[currentAnimation].size() -1;
    
    //if the current frame is outside the last frame 
    if (currentFrameIndex > lastFrame) {
        if ( isLooping ) {
            currentFrameIndex = 0;
        } else {
            currentFrameIndex = 0 ;
        }
    }
    //Current frame of animation is index selected in current animation
    currentFrame = animation.index[currentAnimation][currentFrameIndex];
}

void Sprite::StopAnimation() {
    isAnimated = false;
    currentFrameIndex = 0;
    Animate(0);
}

//Dimensions
//-----------------------------
void Sprite::SetPosition(float x, float y, float z) {
    position.x = x;
    position.y = y;
    position.z = z;
}


void Sprite::SetSize(float x, float y, float z) {
    size.x = x;
    size.y = y;
    size.z = z;
}




//Updates + Physics
//--------------------------

void Sprite::Update(float deltaTime) {
    velocity.x += acceleration.x;
    velocity.y += acceleration.y;
    
    if (velocity.x !=0 && velocity.y != 0)
    {
        isStopped = false;
       // std::cout << "HELLO";
    } else {
        isStopped = true;
    }
    //std::cout << isStopped;

    //If collision, stop jumping
    if ( isColliding ) {
        isJumping = false;
        velocity.y = 0.0f;
        //std::cout << "Is colliding! \n";
    }
    
    //if jumping, apply gravity
    if ( isJumping ) {
        if ( velocity.y < maxGravity.y ) {
            velocity.y = maxGravity.y;
        }
        velocity.y += gravity.y;
        std::cout << "Up up and away! \n";
    }
    
    
    if ( isStopping ) {
        if ( velocity.x > 0 ) {
            velocity.x -= friction.x;
            if ( velocity.x <= 0 ) {
                velocity.x = 0;
                if (!isJumping){
                isStopped = true;
            }
        } else if ( velocity.x < 0 ) {
           velocity.x += friction.x;
            if ( velocity.x >= 0 ) {
                velocity.x = 0;
                if (!isJumping){
                    isStopped = true;
                }
            }
        }
    }
    }
    
    if ( velocity.x > 0 ) {
        isStopped = false;
    }
    
    
    //stopped animation
    if (isStopped){
        switch (direction) {
            case leftd:
                SetAnimation(stoppedl);
                break;
                
            case rightd:
                SetAnimation(stoppedr);
                
            default:
                break;
        }
    }
    
    //running left and right
    if ( velocity.x != 0 ) {
        switch (direction) {
            case leftd:
                SetAnimation(runningl);
                break;
                
            case rightd:
                SetAnimation(runningr);
                break;
                
            default:
                break;
        }
    }
    
    //turning animation
    if ( direction == rightd && velocity.x < 0 ) {
        SetAnimation(turningr);
    }
    if ( direction == leftd && velocity.x > 0 ) {
        SetAnimation(turningl);
    }
    
    //Floor max and min vector
    if ( velocity.x > maxVelocity.x ) {
        velocity.x = maxVelocity.x;
    }
    
    if ( velocity.x < minVelocity.x ) {
        velocity.x = minVelocity.x;
    }
    
    if ( isJumping ) {
        switch (direction) {
            case leftd:
                SetAnimation(jumpingl);
                break;
                
            case rightd:
                SetAnimation(jumpingr);
                break;
                
            default:
                break;
        }
    }
    
    //Final Movement Vector
    position.x += (velocity.x) * deltaTime;
    position.y += (velocity.y) * deltaTime;
}


//Setters
//------------------------------------------------------
void Sprite::SetVelocity(vector2d_t newVelocity) {
    velocity = newVelocity;
}

void Sprite::SetMaxVelocity(vector2d_t newMaxVelocity) {
    maxVelocity = newMaxVelocity;
}

void Sprite::SetMinVelocity(vector2d_t newMinVelocity) {
    minVelocity = newMinVelocity;
}

void Sprite::SetAcceleration(vector2d_t newAcceleration) {
    acceleration = newAcceleration;
}

void Sprite::SetFriction(vector2d_t newFriction) {
    friction = newFriction;
}

void Sprite::SetGravity(vector2d_t newGravity ) {
    gravity = newGravity;
}

void Sprite::SetMaxGravity( vector2d_t newMaxGravity ) {
    maxGravity = newMaxGravity;
}


//Getters

vector2d_t Sprite::GetVelocity() {
    return velocity;
}

vector2d_t Sprite::GetGravity() {
    return gravity;
}

dimensions_t Sprite::GetPosition() {
    return position;
}















