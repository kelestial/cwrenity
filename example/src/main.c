#include <cwrenity.h>

int main(int argc, char const *argv[])
{
	app_info_t info = {"cwrenity - peaceful coding!", 800, 600, false};

	cw_construct_app(info);
	cw_destroy_app();

	return 0;
}