//
// pnetaudio - Portable Networked Audio
//
// Copyright 2011 Thomas de Grivel <billitch@gmail.com>
//
// Permission to use, copy, modify, and distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
// ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
// ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
// OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
//
// macosx/ui/ - User interface for Mac OS X
// pnetaudioAppDelegate - Status bar icon and menu
//

#import "pnetaudioAppDelegate.h"

@implementation pnetaudioAppDelegate

@synthesize statusItem;
@synthesize statusMenu;
@synthesize enableMenuItem;
@synthesize hostMenuItem;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
	statusItem = [[NSStatusBar systemStatusBar] statusItemWithLength:24];
	[statusItem retain];
    [statusItem setTitle:@""];
	[statusItem setImage:[NSImage imageNamed:@"pnetaudio.16.png"]];
	[statusItem setHighlightMode:YES];
    [statusItem setMenu:statusMenu];
}

- (IBAction)doEnable:(id)sender
{
    [enableMenuItem setEnabled:NO];
    
    //TODO: black icon [statusItem setImage:[NSImage imageNamed:@"pnetaudio.16.enabled"]]
    [enableMenuItem setTitle:@"Disable network audio"];
    [enableMenuItem setAction:@selector(doDisable:)];
    [enableMenuItem setEnabled:YES];
}

- (IBAction)doDisable:(id)sender
{
    [enableMenuItem setEnabled:NO];

    //TODO: gray icon [statusItem setImage:[NSImage imageNamed:@"pnetaudio.16.disabled"]]
    [enableMenuItem setTitle:@"Enable network audio"];
    [enableMenuItem setAction:@selector(doEnable:)];
    [enableMenuItem setEnabled:YES];
}

- (IBAction)doQuit:(id)sender
{
    [NSApp terminate:self];
}

@end
