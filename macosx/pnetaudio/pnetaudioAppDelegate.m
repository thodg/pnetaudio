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
