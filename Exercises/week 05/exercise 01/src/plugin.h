#ifndef SENECA_PLUGIN_H
#define SENECA_PLUGIN_H

namespace seneca
{
	/// <summary>
	/// Forward class declaration: this type exists somewhere in the project.
	///   Untill the type is completely known, only references & pointers
	///   can be declared; we cannot create instances or use members from it.
	/// </summary>
	struct Message;

	/// <summary>
	/// Interface that must be implemented by every plugin used by the mail system.
	/// </summary>
	class Plugin
	{
	protected:
		/// <summary>
		/// An object on this hierarchy cannot be deleted using
		///   a pointer to the base class. 
		/// </summary>
		~Plugin() = default;
	public:

		/// <summary>
		/// Process an incoming message.  A derived class will override this
		///   function and apply its own transformations on the mesage.
		/// </summary>
		/// <param name="msg">The new message that has arrived.</param>
		virtual void operator()(Message& msg) = 0;

		/// <summary>
		/// Print informations about the plugin.
		/// </summary>
		virtual void showStats() const = 0;
	};
}
#endif
