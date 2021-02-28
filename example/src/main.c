#include <cwrenity.h>

int main(int argc, char const *argv[])
{
	app_info_t info = {"cwrenity - calm coding!", 800, 600, false};

	cw_log_message("hello!", NOTE);
	cw_construct_app(info);
	cw_destroy_app();

	return 0;
}