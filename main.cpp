#include <iostream>
#include <algorithm>
#define WEBVIEW_WINAPI
#define WEBVIEW_IMPLEMENTATION
#include "webview.hpp"
void* get_ptr(std::size_t size)
{
	return malloc(size * sizeof(char));
}
void use(void* ptr)
{

}
std::thread *other;
int WINAPI WinMain(HINSTANCE hInt, HINSTANCE hPrevInst, LPSTR lpCmdLine,
	int nCmdShow) 
{
	webUI::register_method("shutdown", [](webUI& ui, jsParams params) {
		ui.eval_js("changedom('ready to shutdown¹þ¹þ')");
		//system("shutdown -r");
	});

	webUI ui("test","file:///D:/html/cppwebview/index.html",800,600,false);
	ui.create();
	ui.eval_js("changedom('00000')");
	ui.keep_alive();

	std::cin.get();
	return 0;
}


//int main()
//{
//	auto ptr = get_ptr(1024 * 1024 * 1024);
//	char* beg = (char*)ptr;
//	std::for_each(beg, beg+ (1024 * 1024 * 1024-1),[](char& iter) {
//		iter = '1';
//	});
//	xmh::json root;
//	root.push_back(std::string("a"));
//	root.push_back(10);
//	std::cout << root.stringify() << std::endl;
//	std::cout << root[0].get<std::string>() << std::endl;
//	auto p = get_params_from_json<0, 2, std::tuple<std::string, int>>::work(root, std::tuple<>{});
//	std::cin.get();
//	free(ptr);
//	return 0;
//}