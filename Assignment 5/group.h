# ifndef ASSIGNMENT1_GROUP_H
# define ASSIGNMENT1_GROUP_H

# include "object3d.h"

class Group : public Object3D {
    public:
        Group(int objectNum) : objectNum(objectNum) {
            assert(objectNum > 0);
            objects = new Object3D *[objectNum];
        }

        Group():Group(1){}

        ~Group(){
            delete[] objects;
        }

        void addObject(int index, Object3D *object){
            assert(index<objectNum);
            objects[index] = object;

            auto bb = object->getBoundingBox();
            if (boundingBox == nullptr) 
            {
                boundingBox = new BoundingBox(*bb);
            }
            else if (bb != nullptr) 
            {
                boundingBox->Extend(bb);
            }
        }
        
        bool intersect (const Ray &r, Hit &h, float tMin) override;

        void paint() override;

        void insertIntoGrid(Grid *g, Matrix *m) override;

    private:
        Object3D **objects;
        int objectNum;

};
#endif