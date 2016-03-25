#include "Shader.h"

namespace engine {
	namespace graphics {

		Shader::Shader(GLuint program) {
			m_program = program;
		}

		/* CHANGE LATER TO NO DELET ON ~ */
		Shader::~Shader() {
			glDeleteProgram(m_program);
		}

		void Shader::use() {
			glUseProgram(m_program);
		}

		Shader * Shader::load(const char * name) {
			int vsl;
			std::string* vsa = core::IO::load(SHADER_PATH(name, SHADER_VERTEX), &vsl);
			std::string vs = "";
			for (int i = 0; i < vsl; i++)
				vs += vsa[i];
			int fsl;
			//string* fsa = IO::load(string(SHADER_DIR_LOC + string(name) + "." + SHADER_FRAGMENT).c_str(), &fsl);
			std::string* fsa = core::IO::load(SHADER_PATH(name, SHADER_FRAGMENT), &fsl);
			std::string fs = "";
			for (int i = 0; i < fsl; i++)
				fs += fsa[i];
			return load(vs.c_str(), fs.c_str());
		}

		Shader * Shader::load(const char * vs_text, const char * fs_text) {

			GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

			glShaderSource(vertShader, 1, &vs_text, NULL);
			glCompileShader(vertShader);

			glShaderSource(fragShader, 1, &fs_text, NULL);
			glCompileShader(fragShader);

			GLuint program = glCreateProgram();
			glAttachShader(program, vertShader);
			glAttachShader(program, fragShader);
			glLinkProgram(program);

			GLint result = GL_FALSE;
			glGetProgramiv(program, GL_LINK_STATUS, &result);
			if (result) {
				int logLength;
				glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
				if (logLength > 1) {
					std::vector<char> programError(logLength);
					glGetProgramInfoLog(program, logLength, NULL, &programError[0]);
					std::cout << &programError[0] << std::endl;
				}
			}

			glDeleteShader(vertShader);
			glDeleteShader(fragShader);

			return new Shader(program);
		}
	}
}