xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 62;
 532.71399;702.35602;443.45795;,
 424.16943;496.68582;739.68079;,
 763.00867;272.25046;563.42108;,
 791.43018;547.72949;217.65477;,
 213.30135;156.10710;950.72516;,
 485.87292;-175.35744;840.78668;,
 213.30135;156.10710;950.72516;,
 2.04114;-154.74753;974.57391;,
 158.82561;-474.00525;850.78668;,
 485.87292;-175.35744;840.78668;,
 968.54895;-108.27213;154.70981;,
 947.82245;258.19537;-93.32778;,
 691.41339;-555.88019;432.07617;,
 315.21823;-763.53979;539.80499;,
 691.41339;-555.88019;432.07617;,
 893.34717;-371.91721;-193.26572;,
 926.29462;-26.28909;-339.16379;,
 682.47913;-712.49561;17.77843;,
 395.62088;-883.39240;191.95239;,
 682.47913;-712.49561;17.77843;,
 -366.44971;-112.53426;909.28259;,
 -276.06909;-528.42200;786.32111;,
 -735.33276;-40.59759;656.79559;,
 -760.87665;-433.87903;454.48865;,
 -926.29462;26.28909;339.16379;,
 -947.82245;-258.19537;93.32778;,
 -70.52924;-908.94470;377.61044;,
 -555.33655;-814.40112;45.77847;,
 -791.43018;-547.72949;-217.65477;,
 102.72816;-981.13715;-23.66385;,
 -266.15518;-909.20093;-276.15067;,
 -532.71399;-702.35602;-443.45795;,
 -893.34717;371.91721;193.26572;,
 -968.54895;108.27213;-154.70981;,
 -682.47913;712.49561;-17.77843;,
 -691.41339;555.88019;-432.07617;,
 -395.62088;883.39240;-191.95239;,
 -315.21823;763.53979;-539.80499;,
 -763.00867;-272.25046;-563.42108;,
 -485.87292;175.35744;-840.78668;,
 -158.82561;474.00525;-850.78668;,
 -424.16943;-496.68582;-739.68079;,
 -213.30135;-156.10710;-950.72516;,
 -2.04114;154.74753;-974.57391;,
 -102.72816;981.13715;23.66385;,
 70.52924;908.94470;-377.61044;,
 266.15518;909.20093;276.15067;,
 555.33655;814.40112;-45.77847;,
 276.06909;528.42200;-786.32111;,
 760.87665;433.87903;-454.48865;,
 366.44971;112.53426;-909.28259;,
 735.33276;40.59759;-656.79559;,
 -412.14645;841.85962;308.46667;,
 -689.28174;394.25165;585.83356;,
 72.66078;747.31628;640.29919;,
 -204.47430;299.70816;917.66528;,
 -204.47430;299.70816;917.66528;,
 204.47430;-299.70816;-917.66528;,
 -72.66078;-747.31628;-640.29919;,
 689.28174;-394.25165;-585.83356;,
 412.14645;-841.85962;-308.46667;,
 412.14645;-841.85962;-308.46667;;
 
 108;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;6,7,8,9;,
 4;3,2,10,11;,
 4;2,5,12,10;,
 4;9,8,13,14;,
 4;11,10,15,16;,
 4;10,12,17,15;,
 4;14,13,18,19;,
 4;7,20,21,8;,
 4;20,22,23,21;,
 4;22,24,25,23;,
 4;8,21,26,13;,
 4;21,23,27,26;,
 4;23,25,28,27;,
 4;13,26,29,18;,
 4;26,27,30,29;,
 4;27,28,31,30;,
 4;24,32,33,25;,
 4;32,34,35,33;,
 4;34,36,37,35;,
 4;25,33,38,28;,
 4;33,35,39,38;,
 4;35,37,40,39;,
 4;28,38,41,31;,
 4;38,39,42,41;,
 4;39,40,43,42;,
 4;36,44,45,37;,
 4;44,46,47,45;,
 4;46,0,3,47;,
 4;37,45,48,40;,
 4;45,47,49,48;,
 4;47,3,11,49;,
 4;40,48,50,43;,
 4;48,49,51,50;,
 4;49,11,16,51;,
 4;36,34,52,44;,
 4;34,32,53,52;,
 4;32,24,22,53;,
 4;44,52,54,46;,
 4;52,53,55,54;,
 4;53,22,20,55;,
 4;46,54,1,0;,
 4;54,56,4,1;,
 4;55,20,7,6;,
 4;50,57,42,43;,
 4;57,58,41,42;,
 4;58,30,31,41;,
 4;51,59,57,50;,
 4;59,60,58,57;,
 4;61,29,30,58;,
 4;16,15,59,51;,
 4;15,17,60,59;,
 4;19,18,29,61;,
 4;3,2,1,0;,
 4;2,5,4,1;,
 4;9,8,7,6;,
 4;11,10,2,3;,
 4;10,12,5,2;,
 4;14,13,8,9;,
 4;16,15,10,11;,
 4;15,17,12,10;,
 4;19,18,13,14;,
 4;8,21,20,7;,
 4;21,23,22,20;,
 4;23,25,24,22;,
 4;13,26,21,8;,
 4;26,27,23,21;,
 4;27,28,25,23;,
 4;18,29,26,13;,
 4;29,30,27,26;,
 4;30,31,28,27;,
 4;25,33,32,24;,
 4;33,35,34,32;,
 4;35,37,36,34;,
 4;28,38,33,25;,
 4;38,39,35,33;,
 4;39,40,37,35;,
 4;31,41,38,28;,
 4;41,42,39,38;,
 4;42,43,40,39;,
 4;37,45,44,36;,
 4;45,47,46,44;,
 4;47,3,0,46;,
 4;40,48,45,37;,
 4;48,49,47,45;,
 4;49,11,3,47;,
 4;43,50,48,40;,
 4;50,51,49,48;,
 4;51,16,11,49;,
 4;44,52,34,36;,
 4;52,53,32,34;,
 4;53,22,24,32;,
 4;46,54,52,44;,
 4;54,55,53,52;,
 4;55,20,22,53;,
 4;0,1,54,46;,
 4;1,4,56,54;,
 4;6,7,20,55;,
 4;43,42,57,50;,
 4;42,41,58,57;,
 4;41,31,30,58;,
 4;50,57,59,51;,
 4;57,58,60,59;,
 4;58,30,29,61;,
 4;51,59,15,16;,
 4;59,60,17,15;,
 4;61,29,18,19;;
 
 MeshMaterialList {
  1;
  108;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   1.000000;1.000000;1.000000;0.500000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   1.000000;1.000000;1.000000;;
   TextureFilename {
    "smoke.png";
   }
  }
 }
 MeshNormals {
  98;
  0.539849;0.711763;0.449396;,
  0.434530;0.511475;0.741334;,
  0.209523;0.148061;0.966529;,
  0.795169;0.561599;0.228721;,
  0.791896;0.200666;0.576744;,
  0.558171;-0.176830;0.810664;,
  0.962048;0.252651;-0.103111;,
  0.965241;-0.120253;0.232053;,
  0.731516;-0.497749;0.465973;,
  0.938699;-0.026641;-0.343706;,
  0.908554;-0.366099;-0.201247;,
  0.683547;-0.729513;0.023947;,
  0.002068;-0.156820;0.987625;,
  -0.359773;-0.115737;0.925834;,
  -0.753389;-0.038977;0.656419;,
  0.156030;-0.470689;0.868393;,
  -0.317661;-0.582668;0.748057;,
  -0.726529;-0.502934;0.468203;,
  0.322909;-0.779637;0.536559;,
  -0.144316;-0.903587;0.403366;,
  -0.553184;-0.823852;0.123512;,
  0.400919;-0.895224;0.194522;,
  0.114251;-0.993311;-0.016748;,
  -0.279366;-0.916551;-0.286163;,
  -0.938699;0.026641;0.343706;,
  -0.908554;0.366099;0.201247;,
  -0.683547;0.729513;-0.023947;,
  -0.962047;-0.252651;0.103111;,
  -0.965241;0.120253;-0.232053;,
  -0.731516;0.497749;-0.465973;,
  -0.795169;-0.561599;-0.228721;,
  -0.791896;-0.200666;-0.576744;,
  -0.558171;0.176830;-0.810664;,
  -0.539849;-0.711763;-0.449396;,
  -0.434530;-0.511475;-0.741334;,
  -0.209523;-0.148061;-0.966529;,
  -0.400919;0.895224;-0.194522;,
  -0.114251;0.993311;0.016748;,
  0.279366;0.916551;0.286163;,
  -0.322909;0.779637;-0.536559;,
  0.144316;0.903587;-0.403366;,
  0.553184;0.823852;-0.123512;,
  -0.156030;0.470689;-0.868393;,
  0.317661;0.582668;-0.748057;,
  0.726529;0.502934;-0.468203;,
  -0.002068;0.156820;-0.987625;,
  0.359773;0.115737;-0.925834;,
  0.753389;0.038977;-0.656419;,
  -0.410506;0.826474;0.385259;,
  -0.644232;0.448979;0.619180;,
  -0.001639;0.746740;0.665114;,
  -0.235364;0.369245;0.899034;,
  0.235364;-0.369245;-0.899034;,
  0.001639;-0.746740;-0.665114;,
  0.644232;-0.448979;-0.619180;,
  0.410507;-0.826474;-0.385260;,
  -0.795169;-0.561599;-0.228721;,
  -0.791896;-0.200666;-0.576744;,
  -0.434530;-0.511475;-0.741334;,
  -0.209523;-0.148061;-0.966529;,
  -0.156030;0.470689;-0.868393;,
  -0.002068;0.156820;-0.987625;,
  -0.962048;-0.252651;0.103112;,
  -0.965241;0.120253;-0.232053;,
  -0.908554;0.366099;0.201247;,
  -0.683547;0.729513;-0.023947;,
  0.317661;0.582668;-0.748057;,
  0.726529;0.502934;-0.468203;,
  0.753389;0.038977;-0.656419;,
  0.962047;0.252651;-0.103111;,
  0.938699;-0.026641;-0.343706;,
  0.553184;0.823852;-0.123512;,
  0.795169;0.561599;0.228721;,
  -0.114251;0.993311;0.016748;,
  0.279366;0.916551;0.286163;,
  0.965241;-0.120253;0.232053;,
  0.908554;-0.366099;-0.201247;,
  0.683547;-0.729513;0.023947;,
  0.791896;0.200666;0.576744;,
  0.558171;-0.176830;0.810664;,
  0.156030;-0.470689;0.868393;,
  0.434530;0.511475;0.741334;,
  0.209523;0.148061;0.966529;,
  -0.144316;-0.903587;0.403366;,
  0.114251;-0.993311;-0.016748;,
  -0.553184;-0.823852;0.123512;,
  -0.279366;-0.916551;-0.286163;,
  -0.317661;-0.582668;0.748057;,
  -0.726529;-0.502934;0.468203;,
  -0.359773;-0.115737;0.925834;,
  -0.753389;-0.038977;0.656419;,
  0.410506;-0.826474;-0.385260;,
  0.644232;-0.448979;-0.619180;,
  0.001639;-0.746740;-0.665114;,
  0.235364;-0.369245;-0.899034;,
  -0.235364;0.369245;0.899034;,
  -0.001639;0.746740;0.665114;,
  -0.410507;0.826474;0.385260;;
  108;
  4;0,1,4,3;,
  4;1,2,5,4;,
  4;2,12,15,5;,
  4;3,4,7,6;,
  4;4,5,8,7;,
  4;5,15,18,8;,
  4;6,7,10,9;,
  4;7,8,11,10;,
  4;8,18,21,11;,
  4;12,13,16,15;,
  4;13,14,17,16;,
  4;14,24,27,17;,
  4;15,16,19,18;,
  4;16,17,20,19;,
  4;17,27,30,20;,
  4;18,19,22,21;,
  4;19,20,23,22;,
  4;20,30,33,23;,
  4;24,25,28,27;,
  4;25,26,29,28;,
  4;26,36,39,29;,
  4;27,28,31,30;,
  4;28,29,32,31;,
  4;29,39,42,32;,
  4;30,31,34,33;,
  4;31,32,35,34;,
  4;32,42,45,35;,
  4;36,37,40,39;,
  4;37,38,41,40;,
  4;38,0,3,41;,
  4;39,40,43,42;,
  4;40,41,44,43;,
  4;41,3,6,44;,
  4;42,43,46,45;,
  4;43,44,47,46;,
  4;44,6,9,47;,
  4;36,26,48,37;,
  4;26,25,49,48;,
  4;25,24,14,49;,
  4;37,48,50,38;,
  4;48,49,51,50;,
  4;49,14,13,51;,
  4;38,50,1,0;,
  4;50,51,2,1;,
  4;51,13,12,2;,
  4;46,52,35,45;,
  4;52,53,34,35;,
  4;53,23,33,34;,
  4;47,54,52,46;,
  4;54,55,53,52;,
  4;55,22,23,53;,
  4;9,10,54,47;,
  4;10,11,55,54;,
  4;11,21,22,55;,
  4;56,57,58,33;,
  4;57,32,59,58;,
  4;32,60,61,59;,
  4;62,63,57,56;,
  4;63,29,32,57;,
  4;29,39,60,32;,
  4;24,64,63,62;,
  4;64,65,29,63;,
  4;65,36,39,29;,
  4;60,66,46,61;,
  4;66,67,68,46;,
  4;67,69,70,68;,
  4;39,40,66,60;,
  4;40,71,67,66;,
  4;71,72,69,67;,
  4;36,73,40,39;,
  4;73,74,71,40;,
  4;74,0,72,71;,
  4;69,75,76,70;,
  4;75,8,77,76;,
  4;8,18,21,77;,
  4;72,78,75,69;,
  4;78,79,8,75;,
  4;79,80,18,8;,
  4;0,81,78,72;,
  4;81,82,79,78;,
  4;82,12,80,79;,
  4;18,83,84,21;,
  4;83,85,86,84;,
  4;85,56,33,86;,
  4;80,87,83,18;,
  4;87,88,85,83;,
  4;88,62,56,85;,
  4;12,89,87,80;,
  4;89,90,88,87;,
  4;90,24,62,88;,
  4;84,91,77,21;,
  4;91,92,76,77;,
  4;92,68,70,76;,
  4;86,93,91,84;,
  4;93,94,92,91;,
  4;94,46,68,92;,
  4;33,58,93,86;,
  4;58,59,94,93;,
  4;59,61,46,94;,
  4;12,82,95,89;,
  4;82,81,96,95;,
  4;81,0,74,96;,
  4;89,95,49,90;,
  4;95,96,97,49;,
  4;96,74,73,97;,
  4;90,49,64,24;,
  4;49,97,65,64;,
  4;97,73,36,65;;
 }
 MeshTextureCoords {
  62;
  0.760046;0.306952;,
  0.827270;0.260355;,
  0.827270;0.407293;,
  0.760046;0.431566;,
  0.920570;0.260355;,
  0.920570;0.407293;,
  0.009582;0.260355;,
  0.076806;0.306952;,
  0.076806;0.431566;,
  0.009582;0.407293;,
  0.827270;0.606075;,
  0.760046;0.581802;,
  0.920570;0.606075;,
  0.076806;0.581802;,
  0.009582;0.606075;,
  0.827270;0.753013;,
  0.760046;0.706416;,
  0.920570;0.753013;,
  0.076806;0.706416;,
  0.009582;0.753013;,
  0.144029;0.260355;,
  0.144029;0.407293;,
  0.237329;0.260355;,
  0.237329;0.407293;,
  0.304553;0.306952;,
  0.304553;0.431566;,
  0.144029;0.606075;,
  0.237329;0.606075;,
  0.304553;0.581802;,
  0.144029;0.753013;,
  0.237329;0.753013;,
  0.304553;0.706416;,
  0.371776;0.260355;,
  0.371776;0.407293;,
  0.465076;0.260355;,
  0.465076;0.407293;,
  0.532299;0.306952;,
  0.532299;0.431566;,
  0.371776;0.606075;,
  0.465076;0.606075;,
  0.532299;0.581802;,
  0.371776;0.753013;,
  0.465076;0.753013;,
  0.532299;0.706416;,
  0.599523;0.260355;,
  0.599523;0.407293;,
  0.692823;0.260355;,
  0.692823;0.407293;,
  0.599523;0.606075;,
  0.692823;0.606075;,
  0.599523;0.753013;,
  0.692823;0.753013;,
  0.532299;0.139891;,
  0.304553;0.139891;,
  0.760046;0.139891;,
  0.076806;0.139891;,
  0.987793;0.139891;,
  0.532299;0.873478;,
  0.304553;0.873478;,
  0.760046;0.873478;,
  0.987793;0.873478;,
  0.076806;0.873478;;
 }
}