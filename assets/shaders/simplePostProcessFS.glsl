#version 150

out vec4 FragColor;
in vec2 textureCoords;

uniform sampler2D texture0;
uniform float factor;
uniform bool trigger;

vec4 Sepia( in vec4 color )
{
    return vec4(
          clamp(color.r * 0.393 + color.g * 0.769 + color.b * 0.189, 0.0, 1.0)
        , clamp(color.r * 0.349 + color.g * 0.686 + color.b * 0.168, 0.0, 1.0)
        , clamp(color.r * 0.272 + color.g * 0.534 + color.b * 0.131, 0.0, 1.0)
        , color.a
    );
}

void main()
{
	FragColor = texture(texture0, textureCoords);
	if(trigger)
	{
		FragColor = mix(FragColor, Sepia(FragColor), clamp(factor,0.0,1.0) );
	}

}