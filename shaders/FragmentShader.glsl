#version 330

// Input
in vec2 texcoord;
in vec3 world_position;
in vec3 world_normal;

// Uniform properties
uniform sampler2D texture_1;
uniform int text_rotate;
uniform float deltaX;
uniform float deltaY;
uniform int obj;

uniform vec3 sun_direction;
uniform vec3 eye_position;
uniform float ka;
uniform float kd;
uniform float ks;
uniform int shine;

uniform int all_types[50];
uniform vec3 all_positions[50];
uniform vec3 all_colors[50];

// Output
layout(location = 0) out vec4 out_color;


void main()
{
    vec2 coord = texcoord;
    if(text_rotate == 1)
    {
        coord.x += deltaX;
        coord.y += deltaY;
    }

    vec4 color = texture2D(texture_1, coord);

    if(color.a < 0.5f)
    {
        discard;
    }

    float red=0, green=0, blue=0;
    vec3 N = normalize(world_normal);
	vec3 L = normalize(sun_direction);
	vec3 V = normalize(eye_position - world_position);
	vec3 R = reflect(-L, N);

    float ambient_light = ka * 0.8;
    float diffuse_light = kd * max(dot(N, L), 0);
    float specular_light = ks * pow(max(dot(V, R), 0), shine);
	if (diffuse_light <= 0)
    {
        specular_light = 0;
    }
    red += (ambient_light + diffuse_light + specular_light);
    green += (ambient_light + diffuse_light + specular_light);
    blue += (ambient_light + diffuse_light + specular_light);

    for(int i=0; i<50; i++)
    {
        if(all_types[i] == 0 || all_types[i] == 3 || all_types[i] == 1)
        {
            L = normalize(all_positions[i] - world_position);
            R = reflect(-L, N);

            float cut_off = cos(radians(30.0));
            float spot_light = dot(-L, vec3(0, -1, 0));
            float dis = distance(world_position, all_positions[i]);
            float fac_at_dis = 1 / (1 + dis + dis*dis);
            float fac_at_spot = pow((spot_light - cut_off) / (1 - cut_off), 2);
           

            vec3 diffuse = 3 * all_colors[i] * kd * max(dot(N, L), 0);
            vec3 specular = 3 * all_colors[i] * ks * pow(max(dot(V, R), 0), shine);
            if (diffuse.x == 0)
                specular.x = 0;
            if (diffuse.y == 0)
                specular.y = 0;
            if (diffuse.z == 0)
                specular.z = 0;

            diffuse *= fac_at_dis;
            specular *= fac_at_dis;

            if(all_types[i] == 1)
            {
                if(spot_light > cut_off)
                {
                    diffuse *= fac_at_spot * 8;
                    specular *= fac_at_spot * 8;
                }
                else
                {
                    diffuse *= 0;
                    specular *= 0;
                }
                vec3 poz = all_positions[i];
                poz.x += 3;
                L = normalize(poz - world_position);
                R = reflect(-L, N);

                cut_off = cos(radians(30.0));
                spot_light = dot(-L, vec3(0, -1, 0));
                dis = distance(world_position, poz);
                fac_at_dis = 1 / (1 + dis + dis*dis);
                fac_at_spot = pow((spot_light - cut_off) / (1 - cut_off), 2);
           
                vec3 diffuse2 = 3 * all_colors[i] * kd * max(dot(N, L), 0);
                vec3 specular2 = 3 * all_colors[i] * ks * pow(max(dot(V, R), 0), shine);
                if (diffuse2.x == 0)
                    specular2.x = 0;
                if (diffuse2.y == 0)
                    specular2.y = 0;
                if (diffuse2.z == 0)
                    specular2.z = 0;

                diffuse2 *= fac_at_dis;
                specular2 *= fac_at_dis;

                if(spot_light > cut_off)
                {
                    diffuse2 *= fac_at_spot * 8;
                    specular2 *= fac_at_spot * 8;
                }
                else
                {
                    diffuse2 *= 0;
                    specular2 *= 0;
                }
                red += (diffuse2.x + specular2.x);
                green += (diffuse2.y + specular2.y);
                blue += (diffuse2.z + specular2.z);
            }
            red += (diffuse.x + specular.x);
            green += (diffuse.y + specular.y);
            blue += (diffuse.z + specular.z);
        }
    }
    color.x *= red;
    color.y *= green;
    color.z *= blue;
    out_color = vec4(color.xyz, 1);
}
