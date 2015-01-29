#include "Shader.h"

Shader::Shader() {
}

Shader::Shader(char* vsfile, char* fsfile) {

	vert = glCreateShader(GL_VERTEX_SHADER);
	frag = glCreateShader(GL_FRAGMENT_SHADER);

	const char* vsText = readTextFile(vsfile);
	const char* fsText = readTextFile(fsfile);

	glShaderSource(vert, 1, &vsText, NULL);
	glShaderSource(frag, 1, &fsText, NULL);

	glCompileShader(vert);
	glCompileShader(frag);

	printShaderInfoLog(vert);
	printShaderInfoLog(frag);

	prog = glCreateProgram();

	glAttachShader(prog, vert);
	glAttachShader(prog, frag);

	glLinkProgram(prog);
	printProgramInfoLog(prog);
}

Shader::~Shader() {
	glDetachShader(prog, frag);
	glDetachShader(prog, vert);
    
	glDeleteShader(frag);
	glDeleteShader(vert);
	glDeleteProgram(prog);
}

void Shader::bind() {
	glUseProgram(prog);
}

void Shader::unbind() {
	glUseProgram(0);
}

void Shader::printProgramInfoLog(GLuint obj) {
    int infologLength = 0;
    int charsWritten  = 0;
    char* infoLog;

	glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("%s\n",infoLog);
        free(infoLog);
    }
}

void Shader::printShaderInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

	glGetShaderiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("%s\n",infoLog);
        free(infoLog);
    }
}

char* Shader::readTextFile(char *fn) {
	FILE *fp;
	char *content = NULL;

	int count=0;

	if (fn != NULL) {
		fp = fopen(fn,"rt");

		if (fp != NULL) {
      
		fseek(fp, 0, SEEK_END);
		count = ftell(fp);
		rewind(fp);

		if (count > 0) {
				content = (char *)malloc(sizeof(char) * (count+1));
				count = fread(content,sizeof(char),count,fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
	}
	return content;
}

int Shader::textFileWrite(char *fn, char *s) {
	FILE *fp;
	int status = 0;

	if (fn != NULL) {
		fp = fopen(fn,"w");

		if (fp != NULL) {
			
			if (fwrite(s,sizeof(char),strlen(s),fp) == strlen(s))
				status = 1;
			fclose(fp);
		}
	}
	return(status);
}