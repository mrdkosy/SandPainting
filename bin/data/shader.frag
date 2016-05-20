uniform vec2 resolution;
uniform sampler2DRect _texture;
uniform float coef[9];
uniform float min;

void main(){
    vec2 offset[9];
    offset[0] = vec2(-1.0, -1.0);
    offset[1] = vec2( 0.0, -1.0);
    offset[2] = vec2( 1.0, -1.0);
    offset[3] = vec2(-1.0,  0.0);
    offset[4] = vec2( 0.0,  0.0);
    offset[5] = vec2( 1.0,  0.0);
    offset[6] = vec2(-1.0,  1.0);
    offset[7] = vec2( 0.0,  1.0);
    offset[8] = vec2( 1.0,  1.0);
    
    vec2  fc = vec2(gl_TexCoord[0].x, gl_TexCoord[0].y);
    vec4  destColor = vec4(0.0);
    
    for(int i=0; i<9; i++){
        destColor += texture2DRect(_texture, (fc + offset[i])) * coef[i];
    }
    
    destColor = max(destColor, 0.0);
    
    float grayColor = (destColor.r+destColor.g+destColor.b)/3.;
    
    if( grayColor > min){
        destColor.a = 0.0;
    }else{
        destColor = vec4(1.);
    }
    gl_FragColor = vec4(destColor);
    
}