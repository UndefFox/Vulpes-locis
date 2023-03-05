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
    vec3 pos;
} objectConstants;

void main() {
    gl_Position = ubo.model * vec4(inPosition + objectConstants.pos, 1.0);
    fragLight = clamp(inNormal[0] * 0.53582 + inNormal[1] * 0.3813 + inNormal[2] * 0.75333, 0, 1);
    fragTexCoord = inTexCoord;
}