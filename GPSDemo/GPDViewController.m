//
//  GPDViewController.m
//  GPSDemo
//
//  Created by James Lee on 5/10/14.
//  Copyright (c) 2014 James Lee. All rights reserved.
//

#import "GPDViewController.h"
#import "TWTSideMenuViewController.h"


@interface GPDViewController ()

@end

@implementation GPDViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    [self.navigationController.navigationBar setTintColor:[UIColor darkGrayColor]];
    [self.navigationController.navigationBar setTranslucent:NO];
    [self.navigationController.navigationBar setBarTintColor:[UIColor colorWithWhite:0.95 alpha:1]];
    [self.navigationController.navigationBar setTitleTextAttributes:@{
                                                                      NSFontAttributeName:[UIFont fontWithName:@"OpenSans-Semibold" size:18.0],
                                                                      NSForegroundColorAttributeName:[UIColor darkGrayColor]}];
    
    UIBarButtonItem *openItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:@"menu_icon"]
                                                                 style:UIBarButtonItemStylePlain
                                                                target:self
                                                                action:@selector(openButtonPressed)];

    
    
    if (self.navigationController.viewControllers[0] == self) {
        self.navigationItem.leftBarButtonItem = openItem;
    }
}

- (void)openButtonPressed
{
    [self.view endEditing:YES];
    [self.sideMenuViewController openMenuAnimated:YES completion:nil];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
