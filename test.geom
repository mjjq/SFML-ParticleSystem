layout (points) in;

layout (triangle_strip, max_vertices = 4) out;

in vec3 worldPos[];
in vec4 color[];

varying vec4 colorOut;

varying vec4 TexCoord;

void constructFan(int index,
                  vec2 size)
{
    vec3 LL = worldPos[index] + vec3(-size/2.0, 0.0);
    vec3 LR = worldPos[index] + vec3(size.x/2.0, -size.y/2.0, 0.0);
    vec3 UR = worldPos[index] + vec3(size/2.0, 0.0);
    vec3 UL = worldPos[index] + vec3(-size.x/2.0, size.y/2.0, 0.0);

    gl_Position = vec4(LL, 1.0);
    TexCoord = vec4(0.0, 0.0, 0.0, 1.0);
    EmitVertex();

    gl_Position = vec4(UL, 1.0);
    TexCoord = vec4(0.0, 1.0, 0.0, 1.0);
    EmitVertex();

    gl_Position = vec4(LR, 1.0);
    TexCoord = vec4(1.0, 0.0, 0.0, 1.0);
    EmitVertex();

    gl_Position = vec4(UR, 1.0);
    TexCoord = vec4(1.0, 1.0, 0.0, 1.0);
    EmitVertex();

    EndPrimitive();
}


// Main entry point
void main()
{
    colorOut = color[0];

    constructFan(0, vec2(0.051, 0.051));
    //gl_Position = vec4(worldPos[0], 1.0);
    //EmitVertex();
    EndPrimitive();

}
