//
//  prefWindowController.m
//  pnetaudio
//
//  Created by Thomas de Grivel on 24/10/11.
//  Copyright 2011 Thomas de Grivel. All rights reserved.
//

#import "prefWindowController.h"

@implementation prefWindowController

@synthesize hostField;
@synthesize portField;

- (void)windowDidLoad
{
    [hostField bind:@"value"
           toObject:[NSUserDefaultsController sharedUserDefaultsController]
        withKeyPath:@"values.host"
            options:[NSDictionary dictionaryWithObject:@"192.168.3.42"
                                                forKey:@"NSContinuouslyUpdatesValue"]];
    [hostField retain];
    
    [portField bind:@"value"
           toObject:[NSUserDefaultsController sharedUserDefaultsController]
        withKeyPath:@"values.port"
            options:[NSDictionary dictionaryWithObject:[NSNumber numberWithInteger:9636]
                                                forKey:@"NSContinuouslyUpdatesValue"]];
    [portField retain];
}

- (IBAction)doPreferences:(id)sender
{
    [self showWindow:[self window]];
    [NSApp activateIgnoringOtherApps:YES];
}

@end
