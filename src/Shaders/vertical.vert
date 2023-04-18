#version 450

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out float fragLight;
layout(location = 1) out vec2 fragTexCoord;

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
} ubo;

layout (push_constant) uniform ObjectConstants {
    mat4 model;
} objectConstants;

void main() {
    gl_Position = ubo.model * objectConstants.model * vec4(inPosition, 1.0);
    vec4 normal = objectConstants.model * vec4(inNormal, 0.0f);
    fragLight = clamp(normal[0] * 0.53582 + normal[1] * 0.3813 + normal[2] * 0.75333, 0.05, 1);
    fragTexCoord = inTexCoord;
}