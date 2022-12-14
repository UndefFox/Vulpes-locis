#version 450

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
} ubo;

layout (push_constant) uniform ObjectConstants {
    vec3 pos;
} objectConstants;

void main() {
    gl_Position = ubo.model * vec4(inPosition + objectConstants.pos, 1.0);
    fragColor = vec3(1.0f, 1.0f, 1.0f);
    fragTexCoord = inTexCoord;
}