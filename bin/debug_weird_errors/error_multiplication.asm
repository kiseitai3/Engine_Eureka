        53 [1]	{
0x6d9478bc                   55                       push   %ebp
0x6d9478bd  <+0x0001>        89 e5                    mov    %esp,%ebp
0x6d9478bf  <+0x0003>        57                       push   %edi
0x6d9478c0  <+0x0004>        56                       push   %esi
0x6d9478c1  <+0x0005>        53                       push   %ebx
0x6d9478c2  <+0x0006>        83 ec 4c                 sub    $0x4c,%esp
0x6d9478c5  <+0x0009>        89 4d d4                 mov    %ecx,-0x2c(%ebp)
        55 [1]	    int val = width * frame;
0x6d9478c8  <+0x000c>        8b 45 d4                 mov    -0x2c(%ebp),%eax
0x6d9478cb  <+0x000f>        8b 40 0c                 mov    0xc(%eax),%eax
0x6d9478ce  <+0x0012>        8b 55 d4                 mov    -0x2c(%ebp),%edx
0x6d9478d1  <+0x0015>        8b 12                    mov    (%edx),%edx
0x6d9478d3  <+0x0017>        89 54 24 04              mov    %edx,0x4(%esp)
0x6d9478d7  <+0x001b>        89 04 24                 mov    %eax,(%esp)
0x6d9478da  <+0x001e>        e8 99 c9 01 00           call   0x6d964278 <__mulvsi3>
0x6d9478df  <+0x0023>        89 45 e4                 mov    %eax,-0x1c(%ebp)
        56 [1]	    src.x = width * frame;
0x6d9478e2  <+0x0026>        8b 45 d4                 mov    -0x2c(%ebp),%eax
0x6d9478e5  <+0x0029>        8b 40 0c                 mov    0xc(%eax),%eax
0x6d9478e8  <+0x002c>        8b 55 d4                 mov    -0x2c(%ebp),%edx
0x6d9478eb  <+0x002f>        8b 12                    mov    (%edx),%edx
0x6d9478ed  <+0x0031>        89 54 24 04              mov    %edx,0x4(%esp)
0x6d9478f1  <+0x0035>        89 04 24                 mov    %eax,(%esp)
0x6d9478f4  <+0x0038>        e8 7f c9 01 00           call   0x6d964278 <__mulvsi3>
0x6d9478f9  <+0x003d>        89 c2                    mov    %eax,%edx
0x6d9478fb  <+0x003f>        8b 45 d4                 mov    -0x2c(%ebp),%eax
0x6d9478fe  <+0x0042>        89 50 28                 mov    %edx,0x28(%eax)
        57 [1]	    src.y = height * animNum;
0x6d947901  <+0x0045>        8b 45 d4                 mov    -0x2c(%ebp),%eax
0x6d947904  <+0x0048>        8b 40 08                 mov    0x8(%eax),%eax
0x6d947907  <+0x004b>        8b 55 d4                 mov    -0x2c(%ebp),%edx
0x6d94790a  <+0x004e>        8b 52 10                 mov    0x10(%edx),%edx
0x6d94790d  <+0x0051>        89 54 24 04              mov    %edx,0x4(%esp)
0x6d947911  <+0x0055>        89 04 24                 mov    %eax,(%esp)
0x6d947914  <+0x0058>        e8 5f c9 01 00           call   0x6d964278 <__mulvsi3>
0x6d947919  <+0x005d>        89 c2                    mov    %eax,%edx
0x6d94791b  <+0x005f>        8b 45 d4                 mov    -0x2c(%ebp),%eax
0x6d94791e  <+0x0062>        89 50 2c                 mov    %edx,0x2c(%eax)
        60 [1]	    target.x = x;
0x6d947921  <+0x0065>        8b 45 d4                 mov    -0x2c(%ebp),%eax
0x6d947924  <+0x0068>        8b 55 08                 mov    0x8(%ebp),%edx
0x6d947927  <+0x006b>        89 50 38                 mov    %edx,0x38(%eax)
        61 [1]	    target.y = y;
0x6d94792a  <+0x006e>        8b 45 d4                 mov    -0x2c(%ebp),%eax
0x6d94792d  <+0x0071>        8b 55 0c                 mov    0xc(%ebp),%edx
0x6d947930  <+0x0074>        89 50 3c                 mov    %edx,0x3c(%eax)
        64 [1]	    SDL_RenderCopyEx(&destination, getTextureFromNode(SpriteSheet), &src, &target, rotationDeg, &pivot, flipDir);
0x6d947933  <+0x0077>        8b 45 d4                 mov    -0x2c(%ebp),%eax
0x6d947936  <+0x007a>        8b 58 20                 mov    0x20(%eax),%ebx
0x6d947939  <+0x007d>        8b 45 d4                 mov    -0x2c(%ebp),%eax
0x6d94793c  <+0x0080>        83 c0 48                 add    $0x48,%eax
0x6d94793f  <+0x0083>        89 45 d0                 mov    %eax,-0x30(%ebp)
0x6d947942  <+0x0086>        8b 45 d4                 mov    -0x2c(%ebp),%eax
0x6d947945  <+0x0089>        dd 40 58                 fldl   0x58(%eax)
0x6d947948  <+0x008c>        dd 5d c8                 fstpl  -0x38(%ebp)
0x6d94794b  <+0x008f>        8b 45 d4                 mov    -0x2c(%ebp),%eax
0x6d94794e  <+0x0092>        8d 78 38                 lea    0x38(%eax),%edi
0x6d947951  <+0x0095>        8b 45 d4                 mov    -0x2c(%ebp),%eax
0x6d947954  <+0x0098>        8d 70 28                 lea    0x28(%eax),%esi
0x6d947957  <+0x009b>        8b 45 d4                 mov    -0x2c(%ebp),%eax
0x6d94795a  <+0x009e>        8b 40 24                 mov    0x24(%eax),%eax
0x6d94795d  <+0x00a1>        89 04 24                 mov    %eax,(%esp)
0x6d947960  <+0x00a4>        e8 ff 43 01 00           call   0x6d95bd64 <getTextureFromNode(TexturePacket*)>
0x6d947965  <+0x00a9>        89 5c 24 1c              mov    %ebx,0x1c(%esp)
0x6d947969  <+0x00ad>        8b 4d d0                 mov    -0x30(%ebp),%ecx
0x6d94796c  <+0x00b0>        89 4c 24 18              mov    %ecx,0x18(%esp)
0x6d947970  <+0x00b4>        dd 45 c8                 fldl   -0x38(%ebp)
0x6d947973  <+0x00b7>        dd 5c 24 10              fstpl  0x10(%esp)
0x6d947977  <+0x00bb>        89 7c 24 0c              mov    %edi,0xc(%esp)
0x6d94797b  <+0x00bf>        89 74 24 08              mov    %esi,0x8(%esp)
0x6d94797f  <+0x00c3>        89 44 24 04              mov    %eax,0x4(%esp)
0x6d947983  <+0x00c7>        8b 45 10                 mov    0x10(%ebp),%eax
0x6d947986  <+0x00ca>        89 04 24                 mov    %eax,(%esp)
0x6d947989  <+0x00cd>        e8 d2 c3 01 00           call   0x6d963d60 <SDL_RenderCopyEx>
        65 [1]	    if((frame != frames) && !noLoop)
0x6d94798e  <+0x00d2>        8b 45 d4                 mov    -0x2c(%ebp),%eax
0x6d947991  <+0x00d5>        8b 10                    mov    (%eax),%edx
0x6d947993  <+0x00d7>        8b 45 d4                 mov    -0x2c(%ebp),%eax
0x6d947996  <+0x00da>        8b 40 04                 mov    0x4(%eax),%eax
0x6d947999  <+0x00dd>        39 c2                    cmp    %eax,%edx
0x6d94799b  <+0x00df>        74 62                    je     0x6d9479ff <draw_base::apply_surface(int, int, SDL_Renderer&)+323>
0x6d94799d  <+0x00e1>        8b 45 d4                 mov    -0x2c(%ebp),%eax
0x6d9479a0  <+0x00e4>        8b 40 50                 mov    0x50(%eax),%eax
0x6d9479a3  <+0x00e7>        85 c0                    test   %eax,%eax
0x6d9479a5  <+0x00e9>        75 58                    jne    0x6d9479ff <draw_base::apply_surface(int, int, SDL_Renderer&)+323>
        67 [1]	        if(timeSpentOnFrame == timeBetweenFrames)
0x6d9479a7  <+0x00eb>        8b 45 d4                 mov    -0x2c(%ebp),%eax
0x6d9479aa  <+0x00ee>        8b 50 1c                 mov    0x1c(%eax),%edx
0x6d9479ad  <+0x00f1>        8b 45 d4                 mov    -0x2c(%ebp),%eax
0x6d9479b0  <+0x00f4>        8b 40 18                 mov    0x18(%eax),%eax
0x6d9479b3  <+0x00f7>        39 c2                    cmp    %eax,%edx
0x6d9479b5  <+0x00f9>        75 28                    jne    0x6d9479df <draw_base::apply_surface(int, int, SDL_Renderer&)+291>
        69 [1]	            frame++;
0x6d9479b7  <+0x00fb>        8b 45 d4                 mov    -0x2c(%ebp),%eax
0x6d9479ba  <+0x00fe>        8b 00                    mov    (%eax),%eax
0x6d9479bc  <+0x0100>        c7 44 24 04 01 00 00 00  movl   $0x1,0x4(%esp)
0x6d9479c4  <+0x0108>        89 04 24                 mov    %eax,(%esp)
0x6d9479c7  <+0x010b>        e8 9c c8 01 00           call   0x6d964268 <__addvsi3>
0x6d9479cc  <+0x0110>        89 c2                    mov    %eax,%edx
0x6d9479ce  <+0x0112>        8b 45 d4                 mov    -0x2c(%ebp),%eax
0x6d9479d1  <+0x0115>        89 10                    mov    %edx,(%eax)
        70 [1]	            timeSpentOnFrame = 0;
0x6d9479d3  <+0x0117>        8b 45 d4                 mov    -0x2c(%ebp),%eax
0x6d9479d6  <+0x011a>        c7 40 1c 00 00 00 00     movl   $0x0,0x1c(%eax)
        67 [2]	        if(timeSpentOnFrame == timeBetweenFrames)
0x6d9479dd  <+0x0121>        eb 29                    jmp    0x6d947a08 <draw_base::apply_surface(int, int, SDL_Renderer&)+332>
        74 [1]	            timeSpentOnFrame++;
0x6d9479df  <+0x0123>        8b 45 d4                 mov    -0x2c(%ebp),%eax
0x6d9479e2  <+0x0126>        8b 40 1c                 mov    0x1c(%eax),%eax
0x6d9479e5  <+0x0129>        c7 44 24 04 01 00 00 00  movl   $0x1,0x4(%esp)
0x6d9479ed  <+0x0131>        89 04 24                 mov    %eax,(%esp)
0x6d9479f0  <+0x0134>        e8 73 c8 01 00           call   0x6d964268 <__addvsi3>
0x6d9479f5  <+0x0139>        89 c2                    mov    %eax,%edx
0x6d9479f7  <+0x013b>        8b 45 d4                 mov    -0x2c(%ebp),%eax
0x6d9479fa  <+0x013e>        89 50 1c                 mov    %edx,0x1c(%eax)
        67 [3]	        if(timeSpentOnFrame == timeBetweenFrames)
0x6d9479fd  <+0x0141>        eb 09                    jmp    0x6d947a08 <draw_base::apply_surface(int, int, SDL_Renderer&)+332>
        79 [1]	        frame = 0;
0x6d9479ff  <+0x0143>        8b 45 d4                 mov    -0x2c(%ebp),%eax
0x6d947a02  <+0x0146>        c7 00 00 00 00 00        movl   $0x0,(%eax)
        81 [1]	}
0x6d947a08  <+0x014c>        83 c4 4c                 add    $0x4c,%esp
0x6d947a0b  <+0x014f>        5b                       pop    %ebx
0x6d947a0c  <+0x0150>        5e                       pop    %esi
0x6d947a0d  <+0x0151>        5f                       pop    %edi
0x6d947a0e  <+0x0152>        5d                       pop    %ebp
0x6d947a0f  <+0x0153>        c2 0c 00                 ret    $0xc
