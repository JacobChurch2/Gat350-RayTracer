#include "Materials.h"
#include "Random.h"

bool Lambertian::Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& color, ray_t& scattered) const
{
    glm::vec3 target = raycastHit.point + raycastHit.normal + randomInUnitSphere();
        //<raycast hit point + raycast hit normal + random in unit sphere>
    glm::vec3 direction = glm::normalize(target - raycastHit.point);
        //<create a direction from raycast hit point to the target and normalize it>;

    scattered = ray_t{ raycastHit.point, direction };
        //<set scattered ray with raycast hit point as the origin and the new direction>;
    color = m_albedo;
        //<set color to material albedo>;

    return true;
}

bool Metal::Scatter(const ray_t& ray, const raycastHit_t& raycastHit, glm::vec3& color, ray_t& scattered) const
{
    glm::vec3 reflected = glm::normalize(ray.direction) + raycastHit.normal;
        //<get reflected ray from normalized ray direction and raycast hit normal>;

    // set scattered ray from reflected ray + random point in sphere (fuzz = 0 no randomness, fuzz = 1 random reflected)
    // a mirror has a fuzz value of 0 and a diffused metal surface a higher value
    scattered = ray_t{ raycastHit.point,reflected + randomInUnitSphere() * m_fuzz };
    color = m_albedo;
    // make sure that reflected ray is going away from surface normal (dot product > 0, angle between vectors < 90 degrees)
    return glm::dot(scattered.direction, raycastHit.normal) > 0;
}
