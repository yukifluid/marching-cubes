#include "gl_manager.hpp"
#include "scene.hpp"
#include "object.hpp"
#include "shader.hpp"
#include "material.hpp"
#include "implicit_function.hpp"
#include "nearest_neighbor_search.hpp"
#include "fluid.hpp"

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

void SaveImage(int windowWidth, int windowHeight, std::string imgName);

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        std::cerr << "input config.json data.csv" << std::endl;
        return -1;
    }

    GLManager manager;

    Scene scene;

    Camera camera(glm::vec3(0.0f, 0.5f, 2.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f), 45.0f, (float)manager.getWindowWidth()/manager.getWindowHeight());
    scene.setCamera(camera);

    DirectionalLight light(glm::vec3(1.0f), glm::vec3(1.0f));
    scene.setLight(light);

    // sphere
    // const ImplicitFunction& imp = SphereField(0.5f);
    // const Geometry& geo0 = Metaball(glm::vec3(-0.5f), glm::vec3(0.5f), 10, 0.0f, imp);
    // Material material0(glm::vec3(0.1f, 0.3f, 0.8f));
    // Object obj0(geo0, material0);
    // Shader shader0("shaders/vertex.glsl", "shaders/fragment.glsl");
    // glm::mat4 model0 = glm::mat4(1.0f);
    // scene.AppendObject(obj0, model0, shader0);

    // color field (グリッド分割の仕方)
    // Fluid fluid(std::string(argv[1]), std::string(argv[2]), 30);
    // const ImplicitFunction &imp = ColorField(fluid.config.min_cord, fluid.config.max_cord, fluid.config.fn, fluid.pos, fluid.vol, fluid.config.rho_0, fluid.config.h);
    // const Geometry &geo0 = Metaball(fluid.config.min_cord, fluid.config.max_cord, 30, -0.1f, imp);
    // Material material0(glm::vec3(0.1f, 0.3f, 0.8f));
    // Object obj0(geo0, material0);
    // Shader shader0("shaders/vertex.glsl", "shaders/fragment.glsl");
    // glm::mat4 model0 = glm::mat4(1.0f);
    // scene.AppendObject(obj0, model0, shader0);

    // grid
    // const Geometry &geo1 = Grid(fluid.config.min_cord, fluid.config.max_cord, 20);
    // Material material1(glm::vec3(0.0f));
    // Object obj1(geo1, material1);
    // Shader shader1("shaders/vertex_grid.glsl", "shaders/fragment_grid.glsl");
    // glm::mat4 model1 = glm::mat4(1.0f);
    // scene.AppendObject(obj1, model1, shader1);

    // video
    int framei = 0;

    while (!glfwWindowShouldClose(manager.window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        scene.Reset();

        Fluid fluid(std::string(argv[1]), std::string(argv[2]), framei);
        const ImplicitFunction &imp = ColorField(fluid.config.min_cord, fluid.config.max_cord, fluid.config.fn, fluid.pos, fluid.vol, fluid.config.rho_0, fluid.config.h);
        const Geometry &geo0 = Metaball(fluid.config.min_cord, fluid.config.max_cord, 30, -0.5f, imp);
        Material material0(glm::vec3(0.1f, 0.3f, 0.8f));
        Object obj0(geo0, material0);
        Shader shader0("shaders/vertex.glsl", "shaders/fragment.glsl");
        glm::mat4 model0 = glm::mat4(1.0f);
        scene.AppendObject(obj0, model0, shader0);

        scene.Draw();

        glfwPollEvents();
        glfwSwapBuffers(manager.window);

        // 画像の保存
        std::string frameName = "./frames/capture" + std::to_string(framei) + ".jpg";
        SaveImage(manager.getWindowWidth(), manager.getWindowHeight(), frameName);
        framei++;
        if(framei == 150) glfwSetWindowShouldClose(manager.window, true);
    }
}

// TODO:
// - アニメーション
// - シーンクラスのライト修正

void SaveImage(int windowWidth, int windowHeight, std::string imgName)
{
    const int imageWidth    = windowWidth*2; //twice the size for Mac Retina display
    const int imageHeight   = windowHeight*2; //twice the size for Mac Retina display
    const unsigned int channelNum = 4; // RGBなら3, RGBAなら4
    unsigned char* dataBuffer = NULL;
    dataBuffer = (unsigned char*)malloc(imageWidth * imageHeight * channelNum);

    // 読み取るOpneGLのバッファを指定 GL_FRONT:フロントバッファ　GL_BACK:バックバッファ
    glReadBuffer(GL_FRONT);

    // OpenGLで画面に描画されている内容をバッファに格納
    glReadPixels(
        0,                  //読み取る領域の左下隅のx座標
        0,                  //読み取る領域の左下隅のy座標 //0 or getCurrentWidth() - 1
        imageWidth,         //読み取る領域の幅
        imageHeight,        //読み取る領域の高さ
        GL_BGRA,           //取得したい色情報の形式
        GL_UNSIGNED_BYTE,   //読み取ったデータを保存する配列の型
        dataBuffer          //ビットマップのピクセルデータ（実際にはバイト配列）へのポインタ
    );

    GLubyte* p = static_cast<GLubyte*>(dataBuffer);
    cv::Mat data(imageWidth, imageHeight, CV_8UC4, p);
    cv::flip(data, data, 0);
    cv::imwrite(imgName, data);
}