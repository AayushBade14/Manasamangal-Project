#version 460 core

out vec4 fragColor;

in vec2 TexCoord;

uniform vec2 uRes;
uniform float uTime;

float sdSphere(vec3 p, float r){
  return length(p) - r;
}

float sdPlane(vec3 p, float y){
  return p.y - y;
}

float map(vec3 p){
  return min(sdSphere(p,1.0),sdPlane(p,-1.0));
}

float march(vec3 ro, vec3 rd){
  float t = 0.0;
  for(int i = 0; i < 200; i++){
    vec3 p = ro + t*rd;
    float d = map(p);
    if(d < 0.001) return t;
    t += d;
    if(t > 200.0) break;
  }
  return -1.0;
}

float shadow(vec3 p, vec3 lp){
  vec3 l = normalize(lp - p);
  float t = 0.02;
  float maxDist = length(lp - p);
  float res = 1.0;

  for(int i = 0; i < 200; i++){
    vec3 pos = p + t*l;
    float d = map(pos);
    if(d < 0.001) return 0.0;
    res = min(res,10.0*d/t);
    t += d;
    if(t > maxDist) break;
  }
  return clamp(res,0.0 ,1.0);
}

vec3 getNormal(vec3 p){
  vec2 e = vec2(0.001,0.0);
  float x = map(p + e.xyy) - map(p - e.xyy);
  float y = map(p + e.yxy) - map(p - e.yxy);
  float z = map(p + e.yyx) - map(p - e.yyx);
  return normalize(vec3(x,y,z));
}

void main(){
  vec2 st = gl_FragCoord.xy/uRes;
  vec2 uv = st * 2.0 - 1.0;
  uv.x *= uRes.x/uRes.y; 
  vec3 ro = vec3(3.0*sin(uTime),0.0,3.0*cos(uTime));
  vec3 target = vec3(0.0);
  vec3 fwd = normalize(target - ro);
  vec3 right = normalize(cross(vec3(0.0,1.0,0.0),fwd));
  vec3 up = cross(fwd, right);

  vec3 rd = normalize(uv.x * right + uv.y*up + 1.0 * fwd);

  vec3 lp = vec3(2.0);
  vec3 color = vec3(1.0);

  float t = march(ro, rd);
  if(t > 0.0){
    vec3 p = ro + t*rd;
    vec3 n = getNormal(p);
    vec3 l = normalize(lp - p);
    vec3 v = normalize(ro - p);
    vec3 r = reflect(-l, n);
    
    float sh = shadow(p, lp);
    float diff = max(dot(l,n),0.0)*sh;
    float amb = 0.2;
    float spec = pow(max(dot(r,v),0.0),32.0)*sh;
    vec3 mate = vec3(1.0,0.4,0.0);
    float phong = amb + diff + spec;
    color = mate*phong;
  }
  else{
    vec3 c1 = vec3(0.0,0.2,0.2);
    vec3 c2 = vec3(0.0,0.4,0.7);
    color = mix(c1,c2,rd.y);
  }

  fragColor = vec4(color,1.0);
}
