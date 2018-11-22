function jiadouhao(path)
fid=fopen(path,'a+');
for i=1:659
    for j=1:4
        fprintf(fid,'%i',a(i,j));
        j=j+1;
        if(j<=4)
        fprintf(fid,',');
        end
        
    end
     fprintf(fid,'\n');
end
fclose(fid);