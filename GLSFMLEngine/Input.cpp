//
//  Input.cpp
//  GLSFMLEngine
//
//  Created by Evan Chapman on 3/13/13.
//  Copyright (c) 2013 Evan Chapman. All rights reserved.
//

#include "Input.h"
#include "KeyCodes.h"
#include <iostream>
#include <GLUT/GLUT.h>

buttons_t pressed;

void Keyboard( unsigned char key,int x, int y ) {
    std::cout << "Key: " << key << "\n";
    switch ( key ) {
        case '=':
            pressed.plus = true;
            break;
            
        case '-':
            pressed.minus = true;
            break;
            
        case ']':
            pressed.rbracket = true;
            break;
            
        case '[':
            pressed.lbracket = true;
            break;
            
        case 'w':
            pressed.w = true;
            break;
            
        case 'a':
            pressed.a = true;
            break;
            
        case 's':
            pressed.s = true;
            break;
            
        case 'd':
            pressed.d = true;
            break;
            
        default:
            break;
    }
    if ( glutGetModifiers() == GLUT_ACTIVE_SHIFT ) {
        pressed.shift = true;
    }
}

void KeyboardUp( unsigned char key, int x, int y ) {
    switch ( key ) {
        case '=':
            pressed.plus = false;
            break;
            
        case '-':
            pressed.minus = false;
            break;
            
        case ']':
            pressed.rbracket = false;
            break;
            
        case '[':
            pressed.lbracket = false;
            break;
            
        case 'w':
            pressed.w = false;
            break;
            
        case 'a':
            pressed.a = false;
            break;
            
        case 's':
            pressed.s = false;
            break;
            
        case 'd':
            pressed.d = false;
            break;
            
        case kesc:
            pressed.escape = true;
            break;
    }
}

void SpecialKey( int key, int x, int y ) {
    /*
     Special Key codes:
     Up     = 101
     Down   = 103
     Left   = 100
     Right  = 102
     */
    //std::cout << "Special Key: " << key << "\n";
    switch ( key ) {
        case kup:
            pressed.kup = true;
            break;
            
        case kdown:
            pressed.kdown = true;
            break;
            
        case kleft:
            pressed.kleft = true;
            break;
            
        case kright:
            pressed.kright = true;
            break;
            
        default:
            break;
    }
    if ( glutGetModifiers() == GLUT_ACTIVE_SHIFT ) {
        pressed.shift = true;
    }
}

void SpecialKeyUp( int key, int x, int y ) {
    switch ( key ) {
        case kup:
            pressed.kup = false;
            break;
            
        case kdown:
            pressed.kdown = false;
            break;
            
        case kleft:
            pressed.kleft = false;
            break;
            
        case kright:
            pressed.kright = false;
            break;
            
        default:
            break;
    }
    if ( glutGetModifiers() == GLUT_ACTIVE_SHIFT ) {
        pressed.shift = false;
    }
}

void Joystick(unsigned int buttonMask,int x, int y, int z) {    
   
    if ( x > 3 ) {
        pressed.jright = true;
        pressed.jleft = false;
    }
    
    if (x < 0 ) {
        pressed.jleft = true;
        pressed.jright = false;
    }
    
    if ( x == 3 ) {
        pressed.jright = false;
        pressed.jleft = false;
    }
    
    if ( y > 3 ) {
        pressed.jdown = true;
        pressed.jup = false;
    }
    
    if ( y < 0 ) {
        pressed.jup = true;
        pressed.jdown = false;
    }
    
    if ( y == 3 ) {
        pressed.jdown = false;
        pressed.jup = false;
    }
    
    if ( buttonMask == 8 ) {
        pressed.jbutton1 = true;
    } else {
        pressed.jbutton1 = false;
    }
    
    std::cout << "Joy: " << buttonMask << "\n";
}































