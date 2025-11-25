/**
 * @file Collision_Manager.h
 * @author Ian Codding II
 * @brief 
 * @version 0.1
 * @date 2025-10-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */

 class Collision{

    public:
        int bulletHitCentipede()
        {
            // Check to see if bullet bounds are interacting with centipede bounds

        }
        int bulletHitMushroom()
        {
            // Check to see if bullet bounds are interacting with mushroom bounds

            
        }
        int playerHitCentipede()
        {
            // Check to see if player bounds are interacting with centipede bounds

        }
        void setCollided()
        {
            collided = true;
        }
        bool getCollision()
        {
            return collided;
        }


    private:
        bool collided;

 };
// - Check bullet vs centipede segments
// - Check bullet vs mushrooms
// - Check player vs centipede segments
// - Return collision results to Game class