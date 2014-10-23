//
//  GPDWebViewController.h
//  GPSDemo
//
//  Created by James Lee on 10/10/14.
//  Copyright (c) 2014 James Lee. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "GPDViewController.h"

@interface GPDWebViewController : UIViewController

@property (strong, nonatomic) NSURL *url;
@property (weak, nonatomic) IBOutlet UIWebView *webView;

@end
