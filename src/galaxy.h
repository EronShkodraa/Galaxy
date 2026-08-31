#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <random>
#include <cmath>

struct Star {
    glm::vec3 position;
    glm::vec3 color;
    float size;
    float brightness;
    float orbitSpeed;
    float orbitRadius;
    float angle;
    float heightOffset;
};

struct Nebula {
    glm::vec3 position;
    glm::vec3 color;
    float size;
    float alpha;
    float orbitSpeed;
    float orbitRadius;
    float angle;
};

class Galaxy {
public:
    unsigned int starVAO, starVBO, nebulaVAO, nebulaVBO;
    std::vector<float> starVertices;
    std::vector<float> nebulaVertices;
    std::vector<Star> stars;
    std::vector<Nebula> nebulae;
    float rotationTime = 0.0f;
    
    Galaxy(int starCount, int nebulaCount) {
        generateGalaxy(starCount);
        generateNebulae(nebulaCount);
        setupStarMesh();
        setupNebulaMesh();
    }
    
    glm::vec3 getSpiralColor(float radius, float normalizedRadius) {
        if (normalizedRadius < 0.08f) {
            return glm::vec3(1.0f, 0.9f, 0.7f);
        }
        else if (normalizedRadius < 0.2f) {
            float t = (normalizedRadius - 0.08f) / 0.12f;
            return glm::mix(glm::vec3(1.0f, 0.9f, 0.7f), glm::vec3(1.0f, 0.5f, 0.7f), t);
        }
        else if (normalizedRadius < 0.4f) {
            float t = (normalizedRadius - 0.2f) / 0.2f;
            return glm::mix(glm::vec3(1.0f, 0.5f, 0.7f), glm::vec3(0.8f, 0.4f, 0.9f), t);
        }
        else if (normalizedRadius < 0.6f) {
            float t = (normalizedRadius - 0.4f) / 0.2f;
            return glm::mix(glm::vec3(0.8f, 0.4f, 0.9f), glm::vec3(0.5f, 0.5f, 1.0f), t);
        }
        else if (normalizedRadius < 0.8f) {
            float t = (normalizedRadius - 0.6f) / 0.2f;
            return glm::mix(glm::vec3(0.5f, 0.5f, 1.0f), glm::vec3(0.3f, 0.7f, 0.9f), t);
        }
        else {
            float t = (normalizedRadius - 0.8f) / 0.2f;
            return glm::mix(glm::vec3(0.3f, 0.7f, 0.9f), glm::vec3(0.4f, 0.9f, 0.7f), t);
        }
    }
    
    glm::vec3 getRandomColor(std::mt19937& gen, std::uniform_real_distribution<float>& dis) {
        float choice = dis(gen) * 30.0f;
        
        if (choice < 1.0f) return glm::vec3(1.0f, 0.1f, 0.2f);
        if (choice < 2.0f) return glm::vec3(1.0f, 0.2f, 0.3f);
        if (choice < 3.0f) return glm::vec3(1.0f, 0.3f, 0.5f);
        if (choice < 4.0f) return glm::vec3(1.0f, 0.5f, 0.7f);
        if (choice < 5.0f) return glm::vec3(1.0f, 0.7f, 0.9f);
        if (choice < 6.0f) return glm::vec3(0.8f, 0.2f, 0.8f);
        if (choice < 7.0f) return glm::vec3(0.6f, 0.3f, 1.0f);
        if (choice < 8.0f) return glm::vec3(0.4f, 0.4f, 1.0f);
        if (choice < 9.0f) return glm::vec3(0.3f, 0.5f, 1.0f);
        if (choice < 10.0f) return glm::vec3(0.3f, 0.7f, 1.0f);
        if (choice < 11.0f) return glm::vec3(0.3f, 0.9f, 0.9f);
        if (choice < 12.0f) return glm::vec3(0.2f, 0.8f, 0.5f);
        if (choice < 13.0f) return glm::vec3(0.5f, 0.9f, 0.4f);
        if (choice < 14.0f) return glm::vec3(0.8f, 0.9f, 0.3f);
        if (choice < 15.0f) return glm::vec3(1.0f, 0.9f, 0.4f);
        if (choice < 16.0f) return glm::vec3(1.0f, 0.7f, 0.3f);
        if (choice < 17.0f) return glm::vec3(1.0f, 0.5f, 0.2f);
        if (choice < 18.0f) return glm::vec3(0.9f, 0.2f, 0.5f);
        if (choice < 19.0f) return glm::vec3(0.5f, 0.9f, 0.9f);
        if (choice < 20.0f) return glm::vec3(0.9f, 0.5f, 0.9f);
        if (choice < 21.0f) return glm::vec3(0.1f, 0.8f, 0.9f);
        if (choice < 22.0f) return glm::vec3(0.9f, 0.1f, 0.7f);
        if (choice < 23.0f) return glm::vec3(0.7f, 0.9f, 0.1f);
        if (choice < 24.0f) return glm::vec3(0.9f, 0.7f, 0.1f);
        if (choice < 25.0f) return glm::vec3(0.1f, 0.9f, 0.4f);
        if (choice < 26.0f) return glm::vec3(0.4f, 0.1f, 0.9f);
        if (choice < 27.0f) return glm::vec3(0.9f, 0.1f, 0.1f);
        if (choice < 28.0f) return glm::vec3(0.1f, 0.9f, 0.9f);
        if (choice < 29.0f) return glm::vec3(0.9f, 0.1f, 0.9f);
        return glm::vec3(1.0f, 1.0f, 1.0f);
    }
    
    void generateGalaxy(int count) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(0.0f, 1.0f);
        
        for (int i = 0; i < count; i++) {
            Star star;
            
            float arm = i % 5;
            float baseAngle = arm * (2.0f * 3.14159f / 5.0f);
            float radius = pow(dis(gen), 0.5f) * 90.0f;
            float normalizedRadius = radius / 90.0f;
            
            float armWidth = 0.5f + normalizedRadius * 1.5f;
            float scatter = (dis(gen) - 0.5f) * armWidth;
            
            star.angle = baseAngle + radius * 0.15f + scatter;
            star.orbitRadius = radius;
            star.orbitSpeed = 0.5f / (1.0f + radius * 0.02f);
            star.heightOffset = (dis(gen) - 0.5f) * 1.5f * exp(-normalizedRadius * 3.0f);
            
            float x = cos(star.angle) * star.orbitRadius * 1.3f;
            float z = sin(star.angle) * star.orbitRadius;
            float y = star.heightOffset * 0.3f;
            
            star.position = glm::vec3(x, y, z);
            
            float edgeFade = 1.0f - glm::smoothstep(50.0f, 90.0f, radius);
            
            float colorChoice = dis(gen);
            if (colorChoice < 0.25f) {
                star.color = getSpiralColor(radius, normalizedRadius);
            }
            else {
                star.color = getRandomColor(gen, dis);
                float shade = 0.7f + dis(gen) * 0.6f;
                star.color *= shade;
            }
            
            float brightVariation = dis(gen);
            if (brightVariation < 0.80f) {
                star.size = 0.8f + dis(gen) * 0.8f;
                star.brightness = 0.35f + dis(gen) * 0.25f;
            }
            else if (brightVariation < 0.94f) {
                star.size = 1.0f + dis(gen) * 1.0f;
                star.brightness = 0.55f + dis(gen) * 0.35f;
            }
            else if (brightVariation < 0.99f) {
                star.size = 1.2f + dis(gen) * 1.0f;
                star.brightness = 0.85f + dis(gen) * 0.35f;
            }
            else {
                star.size = 1.3f + dis(gen) * 1.0f;
                star.brightness = 1.3f + dis(gen) * 0.6f;
            }
            
            if (dis(gen) < 0.005f) {
                star.brightness = 2.0f + dis(gen) * 1.0f;
                star.size = 1.5f + dis(gen) * 1.0f;
            }
            
            star.brightness *= edgeFade;
            
            stars.push_back(star);
            
            starVertices.push_back(star.position.x);
            starVertices.push_back(star.position.y);
            starVertices.push_back(star.position.z);
            starVertices.push_back(star.color.r);
            starVertices.push_back(star.color.g);
            starVertices.push_back(star.color.b);
            starVertices.push_back(star.size);
            starVertices.push_back(star.brightness);
        }
        
        for (int i = 0; i < count / 2; i++) {
            Star star;
            float radius = pow(dis(gen), 3.0f) * 25.0f;
            float angle = dis(gen) * 2.0f * 3.14159f;
            float normalizedRadius = radius / 25.0f;
            
            star.position = glm::vec3(
                cos(angle) * radius * 1.3f,
                (dis(gen) - 0.5f) * 1.5f * exp(-normalizedRadius * 2.0f),
                sin(angle) * radius
            );
            
            float colorChoice = dis(gen);
            if (colorChoice < 0.25f) {
                star.color = glm::vec3(1.0f, 0.95f, 0.8f);
            }
            else if (colorChoice < 0.45f) {
                star.color = glm::vec3(1.0f, 0.75f, 0.7f);
            }
            else if (colorChoice < 0.6f) {
                star.color = glm::vec3(1.0f, 0.65f, 0.9f);
            }
            else if (colorChoice < 0.75f) {
                star.color = glm::vec3(0.9f, 0.8f, 1.0f);
            }
            else if (colorChoice < 0.88f) {
                star.color = glm::vec3(0.8f, 0.9f, 1.0f);
            }
            else {
                star.color = getRandomColor(gen, dis);
                float shade = 0.6f + dis(gen) * 0.6f;
                star.color *= shade;
            }
            
            star.size = 1.0f + dis(gen) * 1.5f;
            star.brightness = 0.55f + dis(gen) * 0.55f;
            star.orbitSpeed = 0.8f;
            star.orbitRadius = radius;
            star.angle = angle;
            star.heightOffset = star.position.y;
            
            stars.push_back(star);
            
            starVertices.push_back(star.position.x);
            starVertices.push_back(star.position.y);
            starVertices.push_back(star.position.z);
            starVertices.push_back(star.color.r);
            starVertices.push_back(star.color.g);
            starVertices.push_back(star.color.b);
            starVertices.push_back(star.size);
            starVertices.push_back(star.brightness);
        }
    }
    
    void generateNebulae(int count) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(0.0f, 1.0f);
        
        for (int i = 0; i < count; i++) {
            Nebula neb;
            
            float arm = i % 5;
            float baseAngle = arm * (2.0f * 3.14159f / 5.0f);
            float radius = dis(gen) * 60.0f;
            float angle = baseAngle + radius * 0.15f;
            
            neb.position = glm::vec3(
                cos(angle) * radius * 1.3f,
                (dis(gen) - 0.5f) * 1.5f,
                sin(angle) * radius
            );
            
            neb.color = getRandomColor(gen, dis);
            float shade = 0.6f + dis(gen) * 0.7f;
            neb.color *= shade;
            
            float edgeFade = 1.0f - glm::smoothstep(50.0f, 70.0f, radius);
            neb.size = 1.0f + dis(gen) * 3.0f;
            neb.alpha = (0.02f + dis(gen) * 0.06f) * edgeFade;
            neb.orbitSpeed = 0.5f / (1.0f + radius * 0.02f);
            neb.orbitRadius = radius;
            neb.angle = angle;
            
            nebulae.push_back(neb);
            
            nebulaVertices.push_back(neb.position.x);
            nebulaVertices.push_back(neb.position.y);
            nebulaVertices.push_back(neb.position.z);
            nebulaVertices.push_back(neb.color.r);
            nebulaVertices.push_back(neb.color.g);
            nebulaVertices.push_back(neb.color.b);
            nebulaVertices.push_back(neb.size);
            nebulaVertices.push_back(neb.alpha);
        }
    }
    
    void update(float deltaTime) {
        rotationTime += deltaTime;
        
        starVertices.clear();
        
        for (auto& star : stars) {
            star.angle += star.orbitSpeed * deltaTime;
            
            star.position.x = cos(star.angle) * star.orbitRadius * 1.3f;
            star.position.z = sin(star.angle) * star.orbitRadius;
            star.position.y = star.heightOffset * 0.3f;
            
            starVertices.push_back(star.position.x);
            starVertices.push_back(star.position.y);
            starVertices.push_back(star.position.z);
            starVertices.push_back(star.color.r);
            starVertices.push_back(star.color.g);
            starVertices.push_back(star.color.b);
            starVertices.push_back(star.size);
            starVertices.push_back(star.brightness);
        }
        
        glBindBuffer(GL_ARRAY_BUFFER, starVBO);
        glBufferData(GL_ARRAY_BUFFER, starVertices.size() * sizeof(float), starVertices.data(), GL_DYNAMIC_DRAW);
        
        nebulaVertices.clear();
        
        for (auto& neb : nebulae) {
            neb.angle += neb.orbitSpeed * deltaTime;
            
            neb.position.x = cos(neb.angle) * neb.orbitRadius * 1.3f;
            neb.position.z = sin(neb.angle) * neb.orbitRadius;
            
            nebulaVertices.push_back(neb.position.x);
            nebulaVertices.push_back(neb.position.y);
            nebulaVertices.push_back(neb.position.z);
            nebulaVertices.push_back(neb.color.r);
            nebulaVertices.push_back(neb.color.g);
            nebulaVertices.push_back(neb.color.b);
            nebulaVertices.push_back(neb.size);
            nebulaVertices.push_back(neb.alpha);
        }
        
        glBindBuffer(GL_ARRAY_BUFFER, nebulaVBO);
        glBufferData(GL_ARRAY_BUFFER, nebulaVertices.size() * sizeof(float), nebulaVertices.data(), GL_DYNAMIC_DRAW);
    }
    
    void setupStarMesh() {
        glGenVertexArrays(1, &starVAO);
        glGenBuffers(1, &starVBO);
        
        glBindVertexArray(starVAO);
        glBindBuffer(GL_ARRAY_BUFFER, starVBO);
        glBufferData(GL_ARRAY_BUFFER, starVertices.size() * sizeof(float), starVertices.data(), GL_DYNAMIC_DRAW);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        
        glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
        
        glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(7 * sizeof(float)));
        glEnableVertexAttribArray(3);
    }
    
    void setupNebulaMesh() {
        glGenVertexArrays(1, &nebulaVAO);
        glGenBuffers(1, &nebulaVBO);
        
        glBindVertexArray(nebulaVAO);
        glBindBuffer(GL_ARRAY_BUFFER, nebulaVBO);
        glBufferData(GL_ARRAY_BUFFER, nebulaVertices.size() * sizeof(float), nebulaVertices.data(), GL_DYNAMIC_DRAW);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        
        glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
        
        glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(7 * sizeof(float)));
        glEnableVertexAttribArray(3);
    }
    
    void DrawStars() {
        glBindVertexArray(starVAO);
        glDrawArrays(GL_POINTS, 0, starVertices.size() / 8);
        glBindVertexArray(0);
    }
    
    void DrawNebulae() {
        glBindVertexArray(nebulaVAO);
        glDrawArrays(GL_POINTS, 0, nebulaVertices.size() / 8);
        glBindVertexArray(0);
    }
};