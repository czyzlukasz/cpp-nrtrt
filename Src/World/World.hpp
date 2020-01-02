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
        objects.emplace_back(std::move(object));
    }

    [[nodiscard]] const std::vector<std::unique_ptr<IObject>>& getObjects() const{
        return objects;
    }

    void sortObjects(){
        std::sort(objects.begin(), objects.end(), [](const auto& a, const auto& b){
            return glm::length(a->getCenter()) < glm::length(b->getCenter());
        });
    }

private:
    //TODO: check speed difference of storing unique_ptr against storing Triangle
    std::vector<std::unique_ptr<IObject>> objects;
};


#endif //CPP_NRTRT_WORLD_HPP
