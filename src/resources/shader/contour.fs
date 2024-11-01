#version 430 core

in vec2 fragTexCoord;
out vec4 finalColor;

uniform sampler2D textureSampler;

void main() {
    float alpha = texture(textureSampler, fragTexCoord).a;
    vec4 baseColor = texture(textureSampler, fragTexCoord);

    ivec2 texSize = textureSize(textureSampler, 0); // 0 is the mipmap level, assuming no mipmaps

    float alphaSide = ((fragTexCoord.x > 0.0) ? texture(textureSampler, fragTexCoord + vec2(-1.0 / texSize.x, 0.0)).a : 0.0)
                    + ((fragTexCoord.x < 1.0) ? texture(textureSampler, fragTexCoord + vec2(1.0 / texSize.x, 0.0)).a : 0.0)
                    + ((fragTexCoord.y < 1.0) ? texture(textureSampler, fragTexCoord + vec2(0.0, 1.0 / texSize.y)).a : 0.0)
                    + ((fragTexCoord.y > 0.0) ? texture(textureSampler, fragTexCoord + vec2(0.0, -1.0 / texSize.y)).a : 0.0);

    finalColor = (alpha == 0.0 && alphaSide > 0.0) ? vec4(0.93359375, 0.8984375, 0.87109375, 1.0) : baseColor;
}
