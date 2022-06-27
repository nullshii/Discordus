#include <discord_rpc.h>
#include "OpenSans.h"
#include "imgui_internal.h"
#include <DiscordRPC.h>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <ctime>
#include <cstdio>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imfilebrowser.h>
#include <SimpleIni.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

GLFWwindow *appWindow;
ImFont *appFont;
DiscordRPC *rpc;
CSimpleIniA ini;
ImGui::FileBrowser saveFileDialog(ImGuiFileBrowserFlags_EnterNewFilename | ImGuiFileBrowserFlags_CreateNewDir
								  | ImGuiFileBrowserFlags_CloseOnEsc);
ImGui::FileBrowser loadFileDialog(ImGuiFileBrowserFlags_CloseOnEsc);

static bool useTime = true;
static bool useEndTime = false;
static bool updateTime = true;

static bool useParty = true;

static bool useLargeImage = true;
static bool useSmallImage = true;

char appId[20] = "990661105124786196";

char state[30] = "In Polus";
char details[30] = "Fixing lights";

char elapsedTime[30] = "0";
char endTime[30] = "0";

char partySize[4] = "8";
char partyMax[4] = "12";

char largeImageText[30] = "Discordus";
char largeImagekey[30] = "discordus";

char smallImageText[30] = "Discordus";
char smallImagekey[30] = "discordus";

void quit() { glfwSetWindowShouldClose(appWindow, true); }

void saveToFile() { saveFileDialog.Open(); }

void openFile() { loadFileDialog.Open(); }

void updateStatus()
{
	DiscordRichPresence presence;
	memset(&presence, 0, sizeof(presence));

	if (!strcmp(state, ""))
	{
		strcpy(state, "state");
	}

	if (!strcmp(details, ""))
	{
		strcpy(details, "details");
	}

	presence.state = state;
	presence.details = details;

	if (useLargeImage)
	{
		presence.largeImageKey = largeImagekey;
		presence.largeImageText = largeImageText;
	}

	if (useSmallImage)
	{
		presence.smallImageKey = smallImagekey;
		presence.smallImageText = smallImageText;
	}

	if (updateTime)
	{
		if (useTime)
		{
			presence.startTimestamp = time(0);

			if (useEndTime)
				presence.endTimestamp = time(0) + atoi(endTime);
			else
				presence.startTimestamp -= atoi(elapsedTime);
		}
	}
	else
	{
		DiscordRichPresence oldPresence = rpc->GetPresence();
		presence.startTimestamp = oldPresence.startTimestamp;
		presence.endTimestamp = oldPresence.endTimestamp;
	}

	if (useParty)
	{
		presence.partySize = atoi(partySize);
		presence.partyMax = atoi(partyMax);
	}

	rpc->SetPresence(presence);
	rpc->UpdatePresence();
}

void updateAppId()
{
	if (rpc)
		delete rpc;
	rpc = new DiscordRPC(appId);
	updateStatus();
}

static bool debugMenu = false;

void RenderAppBar()
{
	ImGui::PushFont(appFont);
	{
		ImGui::BeginMainMenuBar();

		if (ImGui::BeginMenu("App"))
		{
			if (ImGui::MenuItem("Update status", "Ctrl + U"))
			{
				updateStatus();
			}

			ImGui::MenuItem("Update time", "Ctrl + T", &updateTime);
			ImGui::MenuItem("Debug menu", "Ctrl + D", &debugMenu);

			if (ImGui::MenuItem("Quit", "Ctrl + Q"))
			{
				quit();
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Save", "Ctrl + S"))
			{
				saveToFile();
			}

			if (ImGui::MenuItem("Open", "Ctrl + O"))
			{
				openFile();
			}

			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}
	ImGui::PopFont();
}

void RenderApp()
{
	if (debugMenu)
	{
		static int w, h;
		ImGui::Begin("Debug menu", &debugMenu);
		glfwGetWindowSize(appWindow, &w, &h);
		ImGui::Text("Window size: %i, %i", w, h);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	ImGui::PushFont(appFont);
	{
		const ImGuiViewport *viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

		ImGui::Begin("Discordus", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);

		ImGui::InputText("Application ID", appId, sizeof(appId));

		if (ImGui::Button("Update Application ID"))
			updateAppId();

		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();

		ImGui::InputText("Details", details, sizeof(details));
		ImGui::InputText("State", state, sizeof(state));

		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();

		ImGui::Checkbox("Use party", &useParty);

		if (useParty)
		{
			ImGui::InputText("Party size", partySize, sizeof(partySize));
			ImGui::InputText("Party max", partyMax, sizeof(partyMax));
		}

		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();

		ImGui::Checkbox("Use time", &useTime);
		ImGui::SameLine();
		ImGui::Checkbox("Use end time", &useEndTime);
		ImGui::SameLine();
		ImGui::Checkbox("Update time", &updateTime);

		if (useTime)
		{
			ImGui::InputText("Elapsed time (in seconds)", elapsedTime, sizeof(elapsedTime));

			if (useEndTime)
				ImGui::InputText("End time (in seconds)", endTime, sizeof(endTime));
		}

		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();

		ImGui::Checkbox("Use large image", &useLargeImage);

		if (useLargeImage)
		{
			ImGui::InputText("Large image key", largeImagekey, sizeof(largeImagekey));
			ImGui::InputText("Large image text", largeImageText, sizeof(largeImageText));
		}

		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();

		ImGui::Checkbox("Use small image", &useSmallImage);

		if (useSmallImage)
		{
			ImGui::InputText("Small image key", smallImagekey, sizeof(smallImagekey));
			ImGui::InputText("Small image text", smallImageText, sizeof(smallImageText));
		}

		ImGui::Separator();

		if (ImGui::Button("Update status"))
		{
			updateStatus();
		}

		ImGui::End();

		ImGui::PopStyleVar(2);
	}
	ImGui::PopFont();

	{
		if (saveFileDialog.HasSelected())
		{
			// TODO: Set values
			ini.SetValue("Discordus", "details", details);

			ini.SaveFile((saveFileDialog.GetSelected().string() + ".ini").c_str());
			saveFileDialog.ClearSelected();
			loadFileDialog.Close();
		}

		if (loadFileDialog.HasSelected())
		{
			ini.LoadFile((loadFileDialog.GetSelected().string() + ".ini").c_str());
			// TODO: Get values

			loadFileDialog.ClearSelected();
			loadFileDialog.Close();
		}
	}
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS && mods == GLFW_MOD_CONTROL && key == GLFW_KEY_Q)
	{
		quit();
	}
	else if (action == GLFW_PRESS && mods == GLFW_MOD_CONTROL && key == GLFW_KEY_S)
	{
		saveToFile();
	}
	else if (action == GLFW_PRESS && mods == GLFW_MOD_CONTROL && key == GLFW_KEY_O)
	{
		openFile();
	}
	else if (action == GLFW_PRESS && mods == GLFW_MOD_CONTROL && key == GLFW_KEY_U)
	{
		updateStatus();
	}
	else if (action == GLFW_PRESS && mods == GLFW_MOD_CONTROL && key == GLFW_KEY_D)
	{
		debugMenu = !debugMenu;
	}
	else if (action == GLFW_PRESS && mods == GLFW_MOD_CONTROL && key == GLFW_KEY_T)
	{
		updateTime = !updateTime;
	}
}

int main(int, char **)
{
	glfwSetErrorCallback([](int error, const char *description) { printf("Glfw Error %i:%s\n", error, description); });

	if (!glfwInit())
		return 1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	appWindow = glfwCreateWindow(555, 555, "Discordus", nullptr, nullptr);
	if (!appWindow)
		return 1;

	glfwMakeContextCurrent(appWindow);
	glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
		return 1;

	glfwSetKeyCallback(appWindow, keyCallback);
	glfwSetWindowSizeCallback(appWindow, [](GLFWwindow *window, int width, int height) { glViewport(0, 0, width, height); });

	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;

	updateAppId();
	saveFileDialog.SetTitle("Save file");
	saveFileDialog.SetTypeFilters({".ini"});
	loadFileDialog.SetTitle("Load file");
	loadFileDialog.SetTypeFilters({".ini"});

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	// io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	// io.ConfigViewportsNoAutoMerge = true;
	// io.ConfigViewportsNoTaskBarIcon = true;

	ImGui::StyleColorsDark();

	ImGuiStyle &style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	ImGui_ImplGlfw_InitForOpenGL(appWindow, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	appFont = io.Fonts->AddFontFromMemoryCompressedTTF(base85_compressed_data, base85_compressed_size, 18);

	while (!glfwWindowShouldClose(appWindow))
	{
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		RenderAppBar();
		saveFileDialog.Display();
		loadFileDialog.Display();
		RenderApp();

		ImGui::Render();
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow *backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}

		glfwSwapBuffers(appWindow);
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	delete rpc;

	glfwDestroyWindow(appWindow);
	glfwTerminate();

	return 0;
}