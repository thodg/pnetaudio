//
//  pnetaudioAppDelegate.m
//  pnetaudio
//
//  Created by Thomas de Grivel on 24/10/11.
//  Copyright 2011 Thomas de Grivel. All rights reserved.
//

#import "pnetaudioAppDelegate.h"

@implementation pnetaudioAppDelegate

@synthesize statusItem;
@synthesize statusMenu;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
	statusItem = [[NSStatusBar systemStatusBar] statusItemWithLength:20];
	[statusItem retain];
    [statusItem setTitle:@""];
	[statusItem setImage:[NSImage imageNamed:@"pnetaudio.16.png"]];
	[statusItem setHighlightMode:YES];

    statusMenu = [NSMenu alloc];
    [statusMenu addItemWithTitle:@"Quit" action:@selector(stop:) keyEquivalent:@""];
    [statusItem setMenu:statusMenu];
}

@end
