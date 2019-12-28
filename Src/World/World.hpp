//
// Created by krawacik3 on 28.12.2019.
//

#ifndef CPP_NRTRT_WORLD_HPP
#define CPP_NRTRT_WORLD_HPP

#include <vector>
#include <Triangle.hpp>
#include <memory>

struct World {
    void addObject(std::unique_ptr<IObject> object){
        objects.push_back(std::move(object));
    }

    [[nodiscard]] const std::vector<std::unique_ptr<IObject>>& getObjects() const{
        return objects;
    }

private:
    //TODO: check speed difference of storing unique_ptr against storing Triangle
    std::vector<std::unique_ptr<IObject>> objects;
};


#endif //CPP_NRTRT_WORLD_HPP
