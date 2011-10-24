//
//  pnetaudioAppDelegate.h
//  pnetaudio
//
//  Created by Thomas de Grivel on 24/10/11.
//  Copyright 2011 Thomas de Grivel. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "prefWindowController.h"

@interface pnetaudioAppDelegate : NSObject <NSApplicationDelegate> {
@private
    NSStatusItem            *statusItem;
    IBOutlet NSMenu         *statusMenu;
    IBOutlet NSMenuItem     *hostMenuItem;
}

@property (retain)          NSStatusItem            *statusItem;
@property (retain) IBOutlet NSMenu                  *statusMenu;
@property (retain) IBOutlet NSMenuItem              *hostMenuItem;

- (IBAction)doQuit:(id)sender;

@end
